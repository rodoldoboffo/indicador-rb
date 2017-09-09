
#define BUFFER_SIZE 256
int _MOSI=5, _MISO=4, _SCLK=3, _RST=2;
byte serialBuffer[BUFFER_SIZE], OK[] = {'O', 'K', ';'};

void setup() {
  pinMode(_MOSI, OUTPUT);
  pinMode(_MISO, INPUT);
  pinMode(_SCLK, OUTPUT);
  pinMode(_RST, OUTPUT);
  digitalWrite(_RST, HIGH);
  Serial.begin(115200);
}

void initializeSPI() {
  digitalWrite(_SCLK, LOW);
  digitalWrite(_MOSI, LOW);
  delay(1);
  digitalWrite(_RST, HIGH);
  delay(1);
  digitalWrite(_RST, LOW);
  delay(20);
}

int transferBit(int b) {
  int response = 0;
  digitalWrite(_SCLK, LOW);
  if (b == 1) {
    digitalWrite(_MOSI, HIGH);
  }
  else {
    digitalWrite(_MOSI, LOW);
  }
  delayMicroseconds(100);
  digitalWrite(_SCLK, HIGH);
  delayMicroseconds(100);
  response = digitalRead(_MISO);
  delayMicroseconds(10); // 10us
  digitalWrite(_SCLK, LOW);
  delayMicroseconds(100); // 10us
  return response;
}

byte transferByteSPI(byte byteToSend) {
  byte response = 0x00, bitToSend;
  byte bitMask = 0x80;
  int responseBit;
  for (int i=0; i<8; i++) {
    bitToSend = byteToSend & bitMask;
    if (bitToSend == 0x80)
      responseBit = transferBit(1);
    else
      responseBit = transferBit(0);
    response = response << 1;
    if (responseBit == HIGH)
      response = response | 0x01;
    byteToSend = byteToSend << 1;
  }
  return response;
}

char* transferBytesSPI(byte *transferBuffer, int len) {
  char response[len];
  int i;
  for (i=0; i<len; i++) {
    response[i] = transferByteSPI(transferBuffer[i]);
  }
  return response;
}

char* runProgram() {
  digitalWrite(_RST, HIGH);
  delay(1);
  digitalWrite(_RST, BUFFER_SIZE);
  delay(1);
  return OK;
}

void clearBuffer() {
  for (int i = 0; i < BUFFER_SIZE; i++)
    serialBuffer[i] = 0;
}

void loop() {
  clearBuffer();
  Serial.readBytesUntil(';', serialBuffer, 256);
  if (serialBuffer[0] == 'T') {
    byte response = transferByteSPI(serialBuffer[1]);
    serialBuffer[0] = response;
    serialBuffer[1] = ';';
    Serial.write(serialBuffer, 2);
  }
  else if (serialBuffer[0] == 'P') {
    initializeSPI();
    Serial.write(OK, 3);
  }
  else if (serialBuffer[0] == 'R') {
    digitalWrite(_RST, HIGH);
    delay(1);
    Serial.write(OK, 3);
  }
}
