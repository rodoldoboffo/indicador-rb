using MicroLibrary;
using System;
using System.Collections.Generic;
using System.ComponentModel;
using System.Data;
using System.Drawing;
using System.IO;
using System.IO.Ports;
using System.Linq;
using System.Text;
using System.Text.RegularExpressions;
using System.Threading;
using System.Threading.Tasks;
using System.Windows.Forms;

namespace UARTTest
{
    public partial class FormMain : Form
    {
        const int FLASH_PAGE_SIZE_BYTES = 128;
        Dictionary<uint, byte[]> memoryMap;
        OpenFileDialog openFileDialog;
        SaveFileDialog saveFileDialog;
        SerialPort serialport;
        Boolean verifyLastSentByte = false;
        byte lastSentSPIByte = 0x00;

        public FormMain()
        {
            InitializeComponent();
            this.serialport = new SerialPort();
            this.saveFileDialog = new SaveFileDialog();
            this.openFileDialog = new OpenFileDialog();
        }

        private void FormMain_Load(object sender, EventArgs e)
        {
            this.initializeSerialPortSelector();
        }

        private void initializeSerialPortSelector()
        {
            this.comboBoxSerialPorts.Items.Clear();
            this.comboBoxSerialPorts.Items.AddRange(SerialPort.GetPortNames());
            if (this.comboBoxSerialPorts.Items.Count > 0)
            {
                this.comboBoxSerialPorts.SelectedIndex = 0;
            } 
        }

        private void disconnect()
        {
            this.serialport.Close();
        }

        private void connect(string portName)
        {
            this.serialport.PortName = portName;
            this.serialport.BaudRate = 115200;
            this.serialport.Handshake = Handshake.None;
            this.serialport.StopBits = StopBits.One;
            this.serialport.Parity = Parity.None;
            this.serialport.Open();
        }

        private void buttonConnect_Click(object sender, EventArgs e)
        {
            String portName = (string) this.comboBoxSerialPorts.Items[this.comboBoxSerialPorts.SelectedIndex];
            this.connect(portName);
        }

        private void buttonDisconnect_Click(object sender, EventArgs e)
        {
            this.disconnect();
        }

        private void buttonLoadProgram_Click(object sender, EventArgs e)
        {
            DialogResult result = this.openFileDialog.ShowDialog();
            if (result == DialogResult.OK)
            {
                StreamReader reader = new System.IO.StreamReader(this.openFileDialog.FileName);
                String content = reader.ReadToEnd();
                reader.Close();
                this.textBoxProgram.Text = content;
            }
        }

        private Dictionary<uint, byte[]> parseHexFile(string content)
        {
            Dictionary<uint, byte[]> memoryMap = new Dictionary<uint, byte[]>();
            content = content.Replace(Environment.NewLine, "\n");

            String pattern = @"^:(\S{2})(\S{4})(00)(\S*)(\S{2})$";
            foreach (string line in content.Split('\n'))
            {
                Regex rgx = new Regex(pattern, RegexOptions.IgnoreCase);
                MatchCollection matches = rgx.Matches(line);
                if (matches.Count > 0)
                {
                    Match m = matches[0];
                    int type = Convert.ToInt32(m.Groups[3].ToString(), 16);
                    if (type == 0x00)
                    {
                        string addressString = m.Groups[2].ToString();
                        uint address = Convert.ToUInt16(addressString, 16);
                        String dataString = m.Groups[4].ToString();
                        byte[] byteStream = new byte[dataString.Length / 2];
                        for (int i = 0; i < dataString.Length / 2; i++)
                        {
                            String byteString = dataString.Substring(2 * i, 2);
                            Byte b = Convert.ToByte(byteString, 16);
                            byteStream[i] = b;
                        }
                        memoryMap[address] = byteStream;
                    }
                }
            }
            return memoryMap;
        }

        private void parseHexFile()
        {
            this.memoryMap = null;
            Dictionary<uint, byte[]> map = this.parseHexFile(this.textBoxProgram.Text);
            uint numBlocks = this.getNumBlocks(map);
            this.updateProgramSizeToolStrip(String.Format("Program size: {0} bytes", numBlocks * FLASH_PAGE_SIZE_BYTES));
            this.memoryMap = map;
        }

        private void buttonBurn_Click(object sender, EventArgs e)
        {
            if (this.memoryMap != null)
            {
                Thread t = new Thread(this.writeProgramMemory);
                t.Start(this.memoryMap);
            }
        }

        private void initProgrammer()
        {
            this.serialport.Write("P;");
            this.serialport.ReadTo(";");
            byte[] response = this.transferBytes(new byte[] { 0xAC, 0x53, 0x00, 0x00 });
            if (response[2] == 0x53)
            {
                this.showMessageDialog("Success!");
            }
            else
            {
                this.showMessageDialog("An error has occured.");
            }
        }

        private void buttonStartProgramProtocol_Click(object sender, EventArgs e)
        {
            Thread t = new Thread(this.initProgrammer);
            t.Start();
        }

        private void updateProgramSizeToolStrip(String text)
        {
            if (InvokeRequired)
            {
                Invoke((MethodInvoker)delegate { updateProgramSizeToolStrip(text); });
                return;
            }
            else
            {
                toolStripStatusLabelProgramSize.Text = text;
            }
        }

        private void showMessageDialog(String message)
        {
            if (InvokeRequired)
            {
                Invoke((MethodInvoker)delegate { showMessageDialog(message); });
                return;
            }
            else
            {
                MessageBox.Show(message);
            }
        }

        private byte[] transferBytes(byte[] bytesToSend)
        {
            byte[] response = new byte[bytesToSend.Length];
            int i;
            for (i = 0; i < bytesToSend.Length; i++)
            {
                byte r = this.transferByte(bytesToSend[i]);
                response[i] = r;
            }
            return response;
        }

        private byte transferByte(byte byteToSend)
        {
            byte[] buffer = new byte[5];
            this.serialport.DiscardInBuffer();
            this.serialport.Write(new byte[] { (Byte)'T', byteToSend, (Byte)';' }, 0, 3);
            while (this.serialport.BytesToRead < 2) ;
            this.serialport.Read(buffer, 0, this.serialport.BytesToRead);
            if (verifyLastSentByte && buffer[0] != lastSentSPIByte)
            {
                Console.WriteLine("SPI Byte validation error!");
            }
            lastSentSPIByte = byteToSend;
            return buffer[0];
        }

        private void chipErase()
        {
            byte[] response = this.transferBytes(new byte[] { 0xAC, 0x80, 0x00, 0x00 });
            Thread.Sleep(10);
            if (response.SequenceEqual(new byte[] { 0x00, 0xAC, 0x80, 0x00 }))
            {
                this.showMessageDialog("Memory Erased!");
            }
            else
            {
                this.showMessageDialog("An error has occured.");
            }
        }

        private void buttonErase_Click(object sender, EventArgs e)
        {
            Thread t = new Thread(this.chipErase);
            t.Start();
        }

        private byte[] getBytesFromMemoryMap(Dictionary<uint, byte[]> map)
        {
            uint numBlocks = this.getNumBlocks(map);
            byte[] bytesToWrite = new byte[FLASH_PAGE_SIZE_BYTES * numBlocks];
            for (int i = 0; i < bytesToWrite.Length; i++)
            {
                bytesToWrite[i] = 0xFF;
            }
            foreach (uint addressOffset in map.Keys)
            {
                byte[] byteArray = map[addressOffset];
                for (uint i = 0; i < byteArray.Length; i++)
                {
                    uint writeAddress = addressOffset + i;
                    bytesToWrite[writeAddress] = byteArray[i];
                }
            }
            return bytesToWrite;
        }

        private List<byte[]> getListOfBlocks(byte[] byteStream)
        {
            List<byte[]> listOfBlocks = new List<byte[]>();
            for (int i=0; i < byteStream.Length / FLASH_PAGE_SIZE_BYTES; i++)
            {
                byte[] chunk = new byte[FLASH_PAGE_SIZE_BYTES];
                Array.Copy(byteStream, i * FLASH_PAGE_SIZE_BYTES, chunk, 0, FLASH_PAGE_SIZE_BYTES);
                listOfBlocks.Add(chunk);
            }
            return listOfBlocks;
        }

        public void writeProgramBin(object memoryMap, object fileName)
        {
            Dictionary<uint, byte[]> map = (Dictionary<uint, byte[]>)memoryMap;
            byte[] bytesToWrite = this.getBytesFromMemoryMap(map);
            List<byte[]> listOfBlocks = this.getListOfBlocks(bytesToWrite);
            FileStream stream = new FileStream((String)fileName, FileMode.Create);
            for (uint i = 0; i < listOfBlocks.Count; i++)
            {
                byte[] byteStream = listOfBlocks[Convert.ToInt32(i)];
                stream.Write(byteStream, 0, byteStream.Length);
            }
            stream.Close();
            this.showMessageDialog("OK");
        }

        public void writeProgramMemory(object memoryMap)
        {
            verifyLastSentByte = true;
            Dictionary<uint, byte[]> map = (Dictionary<uint, byte[]>)memoryMap;
            byte[] bytesToWrite = this.getBytesFromMemoryMap(map);
            List<byte[]> listOfBlocks = this.getListOfBlocks(bytesToWrite);
            for (uint i = 0; i < listOfBlocks.Count; i++)
            {
                /*uint blockAddress = i * FLASH_PAGE_SIZE_BYTES;
                byte[] blockAddressBytes = BitConverter.GetBytes(blockAddress);
                byte[] byteStream = listOfBlocks[Convert.ToInt32(i)];
                byte[] writeCommand = new byte[] { 0x50, blockAddressBytes[1], blockAddressBytes[0] };
                this.transferBytes(writeCommand);
                byte[] response = this.transferBytes(byteStream);*/
                byte[] byteStream = listOfBlocks[Convert.ToInt32(i)];
                uint memoryBlockStartingAddress = i * FLASH_PAGE_SIZE_BYTES;
                uint memoryAddress = memoryBlockStartingAddress;
                for (int j = 0; j < FLASH_PAGE_SIZE_BYTES / 2; j++)
                {
                    byte[] response;
                    byte[] loadAddress = BitConverter.GetBytes(memoryAddress >> 1);
                    byte[] loadCommand = new byte[] { 0x40, 0x00, loadAddress[0], byteStream[j*2] };
                    response = this.transferBytes(loadCommand);

                    loadAddress = BitConverter.GetBytes(memoryAddress >> 1);
                    loadCommand = new byte[] { 0x48, 0x00, loadAddress[0], byteStream[(j * 2)+1] };
                    response = this.transferBytes(loadCommand);
                    
                    memoryAddress += 2;
                }
                byte[] writeAddress = BitConverter.GetBytes(memoryBlockStartingAddress >> 1);
                byte[] writeCommand = new byte[] { 0x4C, writeAddress[1], writeAddress[0], 0x00 };
                this.transferBytes(writeCommand);
            }
            verifyLastSentByte = false;
            this.showMessageDialog("Done!");
        }

        //private byte[] readMemoryBlock(uint blockIndex)
        //{
        //    uint memoryBlockStartingAddress = blockIndex * 64;
        //    byte[] readBlockAddress = BitConverter.GetBytes(memoryBlockStartingAddress);
        //    byte[] blank = new byte[64];
        //    for (int i = 0; i < blank.Length; i++)
        //    {
        //        blank[i] = 0x00;
        //    }
        //    byte[] readCommand = new byte[] { 0x30, readBlockAddress[1], readBlockAddress[0] };
        //    this.transferBytes(readCommand);
        //    byte[] response = this.transferBytes(blank);
        //    return response;
        //}

        //private byte[] readMemoryBlocks(uint numBlocks)
        //{
        //    byte[] response = new byte[] { };
        //    for (uint i = 0; i < numBlocks; i++)
        //    {
        //        byte[] parcel = this.readMemoryBlock(i);
        //        response = response.Concat(parcel).ToArray();
        //    }
        //    return response;
        //}

        private uint getHigherMemoryAddress(Dictionary<uint, byte[]> memoryMap)
        {
            uint higher = 0;
            foreach (uint memoryAddress in memoryMap.Keys)
            {
                uint hMemAddress = memoryAddress + Convert.ToUInt16(memoryMap[memoryAddress].Length) - 1;
                if (higher < hMemAddress)
                {
                    higher = hMemAddress;
                }
            }
            return higher;
        }

        private uint getNumBlocks(Dictionary<uint, byte[]> memoryMap)
        {
            uint higherMemoryAddress = this.getHigherMemoryAddress(memoryMap);
            uint numBlocks = (higherMemoryAddress / FLASH_PAGE_SIZE_BYTES) + 1;
            return numBlocks;
        }

        private void saveContent(string fileName, byte[] content)
        {
            FileStream stream = new FileStream(fileName, FileMode.Create, FileAccess.Write);
            stream.Write(content, 0, content.Length);
            stream.Close();
        }

        private byte[] readMemoryBlock(uint blockIndex)
        {
            uint memoryBlockStartingAddress = blockIndex * FLASH_PAGE_SIZE_BYTES;
            uint memoryAddress = memoryBlockStartingAddress;
            byte[] response = new byte[FLASH_PAGE_SIZE_BYTES];
            for (int i = 0; i < FLASH_PAGE_SIZE_BYTES/2; i++)
            {
                byte[] readAddress = BitConverter.GetBytes(memoryAddress >> 1);
                byte[] readCommand = new byte[] { 0x20, readAddress[1], readAddress[0] };
                this.transferBytes(readCommand);
                response[i*2] = this.transferByte(0);

                readCommand = new byte[] { 0x28, readAddress[1], readAddress[0] };
                this.transferBytes(readCommand);
                response[(i*2)+1] = this.transferByte(0);
                memoryAddress += 2;
            }
            return response;
        }

        private byte[] readDataMemoryBlock(uint blockIndex)
        {
            uint memoryBlockStartingAddress = blockIndex * 32;
            byte[] readBlockAddress = BitConverter.GetBytes(memoryBlockStartingAddress);
            byte[] blank = new byte[32];
            for (int i = 0; i < blank.Length; i++)
            {
                blank[i] = 0x00;
            }
            byte[] readCommand = new byte[] { 0xB0, readBlockAddress[1], readBlockAddress[0] };
            this.transferBytes(readCommand);
            byte[] response = this.transferBytes(blank);
            return response;
        }

        private byte[] readMemoryBlocks(uint numBlocks)
        {
            byte[] response = new byte[] { };
            for (uint i = 0; i < numBlocks; i++)
            {
                byte[] parcel = this.readMemoryBlock(i);
                response = response.Concat(parcel).ToArray();
            }
            return response;
        }

        private byte[] readDataMemoryBlocks(uint numBlocks)
        {
            byte[] response = new byte[] { };
            for (uint i = 0; i < numBlocks; i++)
            {
                byte[] parcel = this.readDataMemoryBlock(i);
                response = response.Concat(parcel).ToArray();
            }
            return response;
        }

        private void saveMemoryContent(object fileName)
        {
            String stringFileName = (string)fileName;
            uint numBlocks = this.getNumBlocks(this.memoryMap);
            byte[] byteStream = this.readMemoryBlocks(numBlocks);
            this.saveContent(stringFileName, byteStream);
            this.showMessageDialog("Done!");
        }

        private void saveDataMemoryContent(object fileName)
        {
            String stringFileName = (string)fileName;
            uint numBlocks = FLASH_PAGE_SIZE_BYTES;
            byte[] byteStream = this.readDataMemoryBlocks(numBlocks);
            this.saveContent(stringFileName, byteStream);
            this.showMessageDialog("Done!");
        }

        private void run()
        {
            this.serialport.Write("R;");
            String response = this.serialport.ReadTo(";");
            this.showMessageDialog(response);
        }

        private void buttonRun_Click(object sender, EventArgs e)
        {
            Thread t = new Thread(this.run);
            t.Start();
        }

        private void dumpButton_Click(object sender, EventArgs e)
        {
            SaveFileDialog s = new SaveFileDialog();
            if (s.ShowDialog() == DialogResult.OK)
            {
                Thread t = new Thread(this.saveMemoryContent);
                t.Start(s.FileName);
            }
        }

        private void buttonGenerateBin_Click(object sender, EventArgs e)
        {
            DialogResult result = this.saveFileDialog.ShowDialog();
            if (result == DialogResult.OK)
            {
                this.writeProgramBin(this.memoryMap, this.saveFileDialog.FileName);
            }
        }

        private void buttonDumpDataMemory_Click(object sender, EventArgs e)
        {
            SaveFileDialog s = new SaveFileDialog();
            if (s.ShowDialog() == DialogResult.OK)
            {
                Thread t = new Thread(this.saveDataMemoryContent);
                t.Start(s.FileName);
            }
        }

        private void button1_Click(object sender, EventArgs e)
        {
            Thread t = new Thread(this.chipErase);
            t.Start();
        }

        private void textBoxProgram_TextChanged(object sender, EventArgs e)
        {
            this.parseHexFile();
        }
    }
}
