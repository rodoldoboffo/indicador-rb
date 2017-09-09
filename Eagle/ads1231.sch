<?xml version="1.0" encoding="utf-8"?>
<!DOCTYPE eagle SYSTEM "eagle.dtd">
<eagle version="7.6.0">
<drawing>
<settings>
<setting alwaysvectorfont="no"/>
<setting verticaltext="up"/>
</settings>
<grid distance="0.1" unitdist="inch" unit="inch" style="lines" multiple="1" display="no" altdistance="0.01" altunitdist="inch" altunit="inch"/>
<layers>
<layer number="1" name="Top" color="4" fill="1" visible="no" active="no"/>
<layer number="2" name="Route2" color="1" fill="3" visible="no" active="no"/>
<layer number="3" name="Route3" color="4" fill="3" visible="no" active="no"/>
<layer number="4" name="Route4" color="1" fill="4" visible="no" active="no"/>
<layer number="5" name="Route5" color="4" fill="4" visible="no" active="no"/>
<layer number="6" name="Route6" color="1" fill="8" visible="no" active="no"/>
<layer number="7" name="Route7" color="4" fill="8" visible="no" active="no"/>
<layer number="8" name="Route8" color="1" fill="2" visible="no" active="no"/>
<layer number="9" name="Route9" color="4" fill="2" visible="no" active="no"/>
<layer number="10" name="Route10" color="1" fill="7" visible="no" active="no"/>
<layer number="11" name="Route11" color="4" fill="7" visible="no" active="no"/>
<layer number="12" name="Route12" color="1" fill="5" visible="no" active="no"/>
<layer number="13" name="Route13" color="4" fill="5" visible="no" active="no"/>
<layer number="14" name="Route14" color="1" fill="6" visible="no" active="no"/>
<layer number="15" name="Route15" color="4" fill="6" visible="no" active="no"/>
<layer number="16" name="Bottom" color="1" fill="1" visible="no" active="no"/>
<layer number="17" name="Pads" color="2" fill="1" visible="no" active="no"/>
<layer number="18" name="Vias" color="2" fill="1" visible="no" active="no"/>
<layer number="19" name="Unrouted" color="6" fill="1" visible="no" active="no"/>
<layer number="20" name="Dimension" color="15" fill="1" visible="no" active="no"/>
<layer number="21" name="tPlace" color="7" fill="1" visible="no" active="no"/>
<layer number="22" name="bPlace" color="7" fill="1" visible="no" active="no"/>
<layer number="23" name="tOrigins" color="15" fill="1" visible="no" active="no"/>
<layer number="24" name="bOrigins" color="15" fill="1" visible="no" active="no"/>
<layer number="25" name="tNames" color="7" fill="1" visible="no" active="no"/>
<layer number="26" name="bNames" color="7" fill="1" visible="no" active="no"/>
<layer number="27" name="tValues" color="7" fill="1" visible="no" active="no"/>
<layer number="28" name="bValues" color="7" fill="1" visible="no" active="no"/>
<layer number="29" name="tStop" color="7" fill="3" visible="no" active="no"/>
<layer number="30" name="bStop" color="7" fill="6" visible="no" active="no"/>
<layer number="31" name="tCream" color="7" fill="4" visible="no" active="no"/>
<layer number="32" name="bCream" color="7" fill="5" visible="no" active="no"/>
<layer number="33" name="tFinish" color="6" fill="3" visible="no" active="no"/>
<layer number="34" name="bFinish" color="6" fill="6" visible="no" active="no"/>
<layer number="35" name="tGlue" color="7" fill="4" visible="no" active="no"/>
<layer number="36" name="bGlue" color="7" fill="5" visible="no" active="no"/>
<layer number="37" name="tTest" color="7" fill="1" visible="no" active="no"/>
<layer number="38" name="bTest" color="7" fill="1" visible="no" active="no"/>
<layer number="39" name="tKeepout" color="4" fill="11" visible="no" active="no"/>
<layer number="40" name="bKeepout" color="1" fill="11" visible="no" active="no"/>
<layer number="41" name="tRestrict" color="4" fill="10" visible="no" active="no"/>
<layer number="42" name="bRestrict" color="1" fill="10" visible="no" active="no"/>
<layer number="43" name="vRestrict" color="2" fill="10" visible="no" active="no"/>
<layer number="44" name="Drills" color="7" fill="1" visible="no" active="no"/>
<layer number="45" name="Holes" color="7" fill="1" visible="no" active="no"/>
<layer number="46" name="Milling" color="3" fill="1" visible="no" active="no"/>
<layer number="47" name="Measures" color="7" fill="1" visible="no" active="no"/>
<layer number="48" name="Document" color="7" fill="1" visible="no" active="no"/>
<layer number="49" name="Reference" color="7" fill="1" visible="no" active="no"/>
<layer number="51" name="tDocu" color="7" fill="1" visible="no" active="no"/>
<layer number="52" name="bDocu" color="7" fill="1" visible="no" active="no"/>
<layer number="90" name="Modules" color="5" fill="1" visible="yes" active="yes"/>
<layer number="91" name="Nets" color="2" fill="1" visible="yes" active="yes"/>
<layer number="92" name="Busses" color="1" fill="1" visible="yes" active="yes"/>
<layer number="93" name="Pins" color="2" fill="1" visible="no" active="yes"/>
<layer number="94" name="Symbols" color="4" fill="1" visible="yes" active="yes"/>
<layer number="95" name="Names" color="7" fill="1" visible="yes" active="yes"/>
<layer number="96" name="Values" color="7" fill="1" visible="yes" active="yes"/>
<layer number="97" name="Info" color="7" fill="1" visible="yes" active="yes"/>
<layer number="98" name="Guide" color="6" fill="1" visible="yes" active="yes"/>
</layers>
<schematic xreflabel="%F%N/%S.%C%R" xrefpart="/%S.%C%R">
<libraries>
<library name="Texas Instruments_By_element14_Batch_1">
<description>Developed by element14 :&lt;br&gt;
element14 CAD Library consolidation.ulp
at 30/07/2012 17:45:58</description>
<packages>
<package name="SOIC127P600X175-16N">
<smd name="1" x="-4.8006" y="8.89" dx="2.0574" dy="0.6096" layer="1"/>
<smd name="2" x="-4.8006" y="7.62" dx="2.0574" dy="0.6096" layer="1"/>
<smd name="3" x="-4.8006" y="6.35" dx="2.0574" dy="0.6096" layer="1"/>
<smd name="4" x="-4.8006" y="5.08" dx="2.0574" dy="0.6096" layer="1"/>
<smd name="5" x="-4.8006" y="3.81" dx="2.0574" dy="0.6096" layer="1"/>
<smd name="6" x="-4.8006" y="2.54" dx="2.0574" dy="0.6096" layer="1"/>
<smd name="7" x="-4.8006" y="1.27" dx="2.0574" dy="0.6096" layer="1"/>
<smd name="8" x="-4.8006" y="0" dx="2.0574" dy="0.6096" layer="1"/>
<smd name="9" x="0" y="0" dx="2.0574" dy="0.6096" layer="1"/>
<smd name="10" x="0" y="1.27" dx="2.0574" dy="0.6096" layer="1"/>
<smd name="11" x="0" y="2.54" dx="2.0574" dy="0.6096" layer="1"/>
<smd name="12" x="0" y="3.81" dx="2.0574" dy="0.6096" layer="1"/>
<smd name="13" x="0" y="5.08" dx="2.0574" dy="0.6096" layer="1"/>
<smd name="14" x="0" y="6.35" dx="2.0574" dy="0.6096" layer="1"/>
<smd name="15" x="0" y="7.62" dx="2.0574" dy="0.6096" layer="1"/>
<smd name="16" x="0" y="8.89" dx="2.0574" dy="0.6096" layer="1"/>
<wire x1="-3.556" y1="-0.5588" x2="-1.2446" y2="-0.5588" width="0.1524" layer="21"/>
<wire x1="-1.2446" y1="9.4488" x2="-2.0828" y2="9.4488" width="0.1524" layer="21"/>
<wire x1="-2.0828" y1="9.4488" x2="-2.6924" y2="9.4488" width="0.1524" layer="21"/>
<wire x1="-2.6924" y1="9.4488" x2="-3.556" y2="9.4488" width="0.1524" layer="21"/>
<wire x1="-2.0828" y1="9.4488" x2="-2.6924" y2="9.4488" width="0" layer="21" curve="-180"/>
<text x="-5.3848" y="9.3218" size="1.27" layer="21" ratio="6" rot="SR0">*</text>
<wire x1="-4.8006" y1="8.89" x2="-4.3942" y2="8.89" width="0.1524" layer="51"/>
<wire x1="-4.8006" y1="7.62" x2="-4.3942" y2="7.62" width="0.1524" layer="51"/>
<wire x1="-4.8006" y1="6.35" x2="-4.3942" y2="6.35" width="0.1524" layer="51"/>
<wire x1="-4.8006" y1="5.08" x2="-4.3942" y2="5.08" width="0.1524" layer="51"/>
<wire x1="-4.8006" y1="3.81" x2="-4.3942" y2="3.81" width="0.1524" layer="51"/>
<wire x1="-4.8006" y1="2.54" x2="-4.3942" y2="2.54" width="0.1524" layer="51"/>
<wire x1="-4.8006" y1="1.27" x2="-4.3942" y2="1.27" width="0.1524" layer="51"/>
<wire x1="-4.8006" y1="0" x2="-4.3942" y2="0" width="0.1524" layer="51"/>
<wire x1="0" y1="0" x2="-0.4064" y2="0" width="0.1524" layer="51"/>
<wire x1="0" y1="1.27" x2="-0.4064" y2="1.27" width="0.1524" layer="51"/>
<wire x1="0" y1="2.54" x2="-0.4064" y2="2.54" width="0.1524" layer="51"/>
<wire x1="0" y1="3.81" x2="-0.4064" y2="3.81" width="0.1524" layer="51"/>
<wire x1="0" y1="5.08" x2="-0.4064" y2="5.08" width="0.1524" layer="51"/>
<wire x1="0" y1="6.35" x2="-0.4064" y2="6.35" width="0.1524" layer="51"/>
<wire x1="0" y1="7.62" x2="-0.4064" y2="7.62" width="0.1524" layer="51"/>
<wire x1="0" y1="8.89" x2="-0.4064" y2="8.89" width="0.1524" layer="51"/>
<wire x1="-4.3942" y1="-0.5588" x2="-0.4064" y2="-0.5588" width="0.1524" layer="51"/>
<wire x1="-0.4064" y1="-0.5588" x2="-0.4064" y2="9.4488" width="0.1524" layer="51"/>
<wire x1="-0.4064" y1="9.4488" x2="-2.0828" y2="9.4488" width="0.1524" layer="51"/>
<wire x1="-2.0828" y1="9.4488" x2="-2.6924" y2="9.4488" width="0.1524" layer="51"/>
<wire x1="-2.6924" y1="9.4488" x2="-4.3942" y2="9.4488" width="0.1524" layer="51"/>
<wire x1="-4.3942" y1="9.4488" x2="-4.3942" y2="-0.5588" width="0.1524" layer="51"/>
<wire x1="-2.0828" y1="9.4488" x2="-2.6924" y2="9.4488" width="0" layer="51" curve="-180"/>
<text x="-5.3848" y="9.3218" size="1.27" layer="51" ratio="6" rot="SR0">*</text>
<text x="-7.1628" y="10.4394" size="2.0828" layer="25" ratio="10" rot="SR0">&gt;NAME</text>
<text x="-7.9248" y="-3.6576" size="2.0828" layer="27" ratio="10" rot="SR0">&gt;VALUE</text>
</package>
</packages>
<symbols>
<symbol name="ADS1231ID">
<pin name="AVDD" x="-22.86" y="17.78" length="middle" direction="pwr"/>
<pin name="DVDD" x="-22.86" y="15.24" length="middle" direction="pwr"/>
<pin name="SCLK" x="-22.86" y="10.16" length="middle" direction="in"/>
<pin name="CLKIN" x="-22.86" y="7.62" length="middle" direction="in"/>
<pin name="PSW" x="-22.86" y="2.54" length="middle" direction="in"/>
<pin name="~PDWN" x="-22.86" y="0" length="middle" direction="in"/>
<pin name="SPEED" x="-22.86" y="-2.54" length="middle" direction="in"/>
<pin name="CAP_2" x="-22.86" y="-5.08" length="middle" direction="in"/>
<pin name="CAP" x="-22.86" y="-7.62" length="middle" direction="in"/>
<pin name="AINP" x="-22.86" y="-10.16" length="middle" direction="in"/>
<pin name="AINN" x="-22.86" y="-12.7" length="middle" direction="in"/>
<pin name="VREFP" x="-22.86" y="-15.24" length="middle" direction="in"/>
<pin name="VREFN" x="-22.86" y="-17.78" length="middle" direction="in"/>
<pin name="GND_2" x="-22.86" y="-22.86" length="middle" direction="pas"/>
<pin name="GND" x="-22.86" y="-25.4" length="middle" direction="pas"/>
<pin name="~DRDY/DOUT" x="22.86" y="17.78" length="middle" direction="out" rot="R180"/>
<wire x1="-17.78" y1="25.4" x2="-17.78" y2="-30.48" width="0.4064" layer="94"/>
<wire x1="-17.78" y1="-30.48" x2="17.78" y2="-30.48" width="0.4064" layer="94"/>
<wire x1="17.78" y1="-30.48" x2="17.78" y2="25.4" width="0.4064" layer="94"/>
<wire x1="17.78" y1="25.4" x2="-17.78" y2="25.4" width="0.4064" layer="94"/>
<text x="-5.3594" y="29.4386" size="2.0828" layer="95" ratio="10" rot="SR0">&gt;NAME</text>
<text x="-6.2738" y="-37.211" size="2.0828" layer="96" ratio="10" rot="SR0">&gt;VALUE</text>
</symbol>
</symbols>
<devicesets>
<deviceset name="ADS1231ID" prefix="U">
<description>ADC</description>
<gates>
<gate name="A" symbol="ADS1231ID" x="0" y="0"/>
</gates>
<devices>
<device name="" package="SOIC127P600X175-16N">
<connects>
<connect gate="A" pin="AINN" pad="8"/>
<connect gate="A" pin="AINP" pad="7"/>
<connect gate="A" pin="AVDD" pad="13"/>
<connect gate="A" pin="CAP" pad="6"/>
<connect gate="A" pin="CAP_2" pad="5"/>
<connect gate="A" pin="CLKIN" pad="3"/>
<connect gate="A" pin="DVDD" pad="1"/>
<connect gate="A" pin="GND" pad="11"/>
<connect gate="A" pin="GND_2" pad="2"/>
<connect gate="A" pin="PSW" pad="12"/>
<connect gate="A" pin="SCLK" pad="15"/>
<connect gate="A" pin="SPEED" pad="4"/>
<connect gate="A" pin="VREFN" pad="9"/>
<connect gate="A" pin="VREFP" pad="10"/>
<connect gate="A" pin="~DRDY/DOUT" pad="16"/>
<connect gate="A" pin="~PDWN" pad="14"/>
</connects>
<technologies>
<technology name="">
<attribute name="MPN" value="ADS1231ID" constant="no"/>
<attribute name="OC_FARNELL" value="1882261" constant="no"/>
<attribute name="OC_NEWARK" value="27T6158" constant="no"/>
<attribute name="PACKAGE" value="SOIC-16" constant="no"/>
<attribute name="SUPPLIER" value="Texas Instruments" constant="no"/>
</technology>
</technologies>
</device>
</devices>
</deviceset>
</devicesets>
</library>
<library name="con-lsta">
<description>&lt;b&gt;Female Headers etc.&lt;/b&gt;&lt;p&gt;
Naming:&lt;p&gt;
FE = female&lt;p&gt;
# contacts - # rows&lt;p&gt;
W = angled&lt;p&gt;
&lt;author&gt;Created by librarian@cadsoft.de&lt;/author&gt;</description>
<packages>
<package name="FE08">
<description>&lt;b&gt;FEMALE HEADER&lt;/b&gt;</description>
<wire x1="-10.16" y1="1.27" x2="-10.16" y2="-1.27" width="0.1524" layer="21"/>
<wire x1="-10.16" y1="-1.27" x2="-7.874" y2="-1.27" width="0.1524" layer="21"/>
<wire x1="-7.874" y1="-1.27" x2="-7.62" y2="-1.016" width="0.1524" layer="21"/>
<wire x1="-7.62" y1="-1.016" x2="-7.366" y2="-1.27" width="0.1524" layer="21"/>
<wire x1="-7.366" y1="-1.27" x2="-5.334" y2="-1.27" width="0.1524" layer="21"/>
<wire x1="-5.334" y1="-1.27" x2="-5.08" y2="-1.016" width="0.1524" layer="21"/>
<wire x1="-5.08" y1="-1.016" x2="-4.826" y2="-1.27" width="0.1524" layer="21"/>
<wire x1="-4.826" y1="-1.27" x2="-2.794" y2="-1.27" width="0.1524" layer="21"/>
<wire x1="-2.794" y1="-1.27" x2="-2.54" y2="-1.016" width="0.1524" layer="21"/>
<wire x1="-2.54" y1="-1.016" x2="-2.286" y2="-1.27" width="0.1524" layer="21"/>
<wire x1="-2.286" y1="-1.27" x2="-0.254" y2="-1.27" width="0.1524" layer="21"/>
<wire x1="-0.254" y1="-1.27" x2="0" y2="-1.016" width="0.1524" layer="21"/>
<wire x1="0" y1="-1.016" x2="0.254" y2="-1.27" width="0.1524" layer="21"/>
<wire x1="0.254" y1="1.27" x2="0" y2="1.016" width="0.1524" layer="21"/>
<wire x1="0" y1="1.016" x2="-0.254" y2="1.27" width="0.1524" layer="21"/>
<wire x1="-0.254" y1="1.27" x2="-2.286" y2="1.27" width="0.1524" layer="21"/>
<wire x1="-2.286" y1="1.27" x2="-2.54" y2="1.016" width="0.1524" layer="21"/>
<wire x1="-2.54" y1="1.016" x2="-2.794" y2="1.27" width="0.1524" layer="21"/>
<wire x1="-2.794" y1="1.27" x2="-4.826" y2="1.27" width="0.1524" layer="21"/>
<wire x1="-4.826" y1="1.27" x2="-5.08" y2="1.016" width="0.1524" layer="21"/>
<wire x1="-5.08" y1="1.016" x2="-5.334" y2="1.27" width="0.1524" layer="21"/>
<wire x1="-5.334" y1="1.27" x2="-7.366" y2="1.27" width="0.1524" layer="21"/>
<wire x1="-7.366" y1="1.27" x2="-7.62" y2="1.016" width="0.1524" layer="21"/>
<wire x1="-7.62" y1="1.016" x2="-7.874" y2="1.27" width="0.1524" layer="21"/>
<wire x1="-7.874" y1="1.27" x2="-10.16" y2="1.27" width="0.1524" layer="21"/>
<wire x1="-9.144" y1="0.762" x2="-9.144" y2="0.508" width="0.1524" layer="51"/>
<wire x1="-9.144" y1="0.508" x2="-9.398" y2="0.508" width="0.1524" layer="51"/>
<wire x1="-9.398" y1="0.508" x2="-9.398" y2="-0.508" width="0.1524" layer="51"/>
<wire x1="-9.398" y1="-0.508" x2="-9.144" y2="-0.508" width="0.1524" layer="51"/>
<wire x1="-9.144" y1="-0.508" x2="-9.144" y2="-0.762" width="0.1524" layer="51"/>
<wire x1="-9.144" y1="-0.762" x2="-8.636" y2="-0.762" width="0.1524" layer="51"/>
<wire x1="-8.636" y1="-0.762" x2="-8.636" y2="-0.508" width="0.1524" layer="51"/>
<wire x1="-8.636" y1="-0.508" x2="-8.382" y2="-0.508" width="0.1524" layer="51"/>
<wire x1="-8.382" y1="-0.508" x2="-8.382" y2="0.508" width="0.1524" layer="51"/>
<wire x1="-8.382" y1="0.508" x2="-8.636" y2="0.508" width="0.1524" layer="51"/>
<wire x1="-8.636" y1="0.508" x2="-8.636" y2="0.762" width="0.1524" layer="51"/>
<wire x1="-8.636" y1="0.762" x2="-9.144" y2="0.762" width="0.1524" layer="51"/>
<wire x1="-6.604" y1="0.762" x2="-6.604" y2="0.508" width="0.1524" layer="51"/>
<wire x1="-6.604" y1="0.508" x2="-6.858" y2="0.508" width="0.1524" layer="51"/>
<wire x1="-6.858" y1="0.508" x2="-6.858" y2="-0.508" width="0.1524" layer="51"/>
<wire x1="-6.858" y1="-0.508" x2="-6.604" y2="-0.508" width="0.1524" layer="51"/>
<wire x1="-6.604" y1="-0.508" x2="-6.604" y2="-0.762" width="0.1524" layer="51"/>
<wire x1="-6.604" y1="-0.762" x2="-6.096" y2="-0.762" width="0.1524" layer="51"/>
<wire x1="-6.096" y1="-0.762" x2="-6.096" y2="-0.508" width="0.1524" layer="51"/>
<wire x1="-6.096" y1="-0.508" x2="-5.842" y2="-0.508" width="0.1524" layer="51"/>
<wire x1="-5.842" y1="-0.508" x2="-5.842" y2="0.508" width="0.1524" layer="51"/>
<wire x1="-5.842" y1="0.508" x2="-6.096" y2="0.508" width="0.1524" layer="51"/>
<wire x1="-6.096" y1="0.508" x2="-6.096" y2="0.762" width="0.1524" layer="51"/>
<wire x1="-6.096" y1="0.762" x2="-6.604" y2="0.762" width="0.1524" layer="51"/>
<wire x1="-4.064" y1="0.762" x2="-4.064" y2="0.508" width="0.1524" layer="51"/>
<wire x1="-4.064" y1="0.508" x2="-4.318" y2="0.508" width="0.1524" layer="51"/>
<wire x1="-4.318" y1="0.508" x2="-4.318" y2="-0.508" width="0.1524" layer="51"/>
<wire x1="-4.318" y1="-0.508" x2="-4.064" y2="-0.508" width="0.1524" layer="51"/>
<wire x1="-4.064" y1="-0.508" x2="-4.064" y2="-0.762" width="0.1524" layer="51"/>
<wire x1="-4.064" y1="-0.762" x2="-3.556" y2="-0.762" width="0.1524" layer="51"/>
<wire x1="-3.556" y1="-0.762" x2="-3.556" y2="-0.508" width="0.1524" layer="51"/>
<wire x1="-3.556" y1="-0.508" x2="-3.302" y2="-0.508" width="0.1524" layer="51"/>
<wire x1="-3.302" y1="-0.508" x2="-3.302" y2="0.508" width="0.1524" layer="51"/>
<wire x1="-3.302" y1="0.508" x2="-3.556" y2="0.508" width="0.1524" layer="51"/>
<wire x1="-3.556" y1="0.508" x2="-3.556" y2="0.762" width="0.1524" layer="51"/>
<wire x1="-3.556" y1="0.762" x2="-4.064" y2="0.762" width="0.1524" layer="51"/>
<wire x1="-1.524" y1="0.762" x2="-1.524" y2="0.508" width="0.1524" layer="51"/>
<wire x1="-1.524" y1="0.508" x2="-1.778" y2="0.508" width="0.1524" layer="51"/>
<wire x1="-1.778" y1="0.508" x2="-1.778" y2="-0.508" width="0.1524" layer="51"/>
<wire x1="-1.778" y1="-0.508" x2="-1.524" y2="-0.508" width="0.1524" layer="51"/>
<wire x1="-1.524" y1="-0.508" x2="-1.524" y2="-0.762" width="0.1524" layer="51"/>
<wire x1="-1.524" y1="-0.762" x2="-1.016" y2="-0.762" width="0.1524" layer="51"/>
<wire x1="-1.016" y1="-0.762" x2="-1.016" y2="-0.508" width="0.1524" layer="51"/>
<wire x1="-1.016" y1="-0.508" x2="-0.762" y2="-0.508" width="0.1524" layer="51"/>
<wire x1="-0.762" y1="-0.508" x2="-0.762" y2="0.508" width="0.1524" layer="51"/>
<wire x1="-0.762" y1="0.508" x2="-1.016" y2="0.508" width="0.1524" layer="51"/>
<wire x1="-1.016" y1="0.508" x2="-1.016" y2="0.762" width="0.1524" layer="51"/>
<wire x1="-1.016" y1="0.762" x2="-1.524" y2="0.762" width="0.1524" layer="51"/>
<wire x1="1.016" y1="0.762" x2="1.016" y2="0.508" width="0.1524" layer="51"/>
<wire x1="1.016" y1="0.508" x2="0.762" y2="0.508" width="0.1524" layer="51"/>
<wire x1="0.762" y1="0.508" x2="0.762" y2="-0.508" width="0.1524" layer="51"/>
<wire x1="0.762" y1="-0.508" x2="1.016" y2="-0.508" width="0.1524" layer="51"/>
<wire x1="1.016" y1="-0.508" x2="1.016" y2="-0.762" width="0.1524" layer="51"/>
<wire x1="1.016" y1="-0.762" x2="1.524" y2="-0.762" width="0.1524" layer="51"/>
<wire x1="1.524" y1="-0.762" x2="1.524" y2="-0.508" width="0.1524" layer="51"/>
<wire x1="1.524" y1="-0.508" x2="1.778" y2="-0.508" width="0.1524" layer="51"/>
<wire x1="1.778" y1="-0.508" x2="1.778" y2="0.508" width="0.1524" layer="51"/>
<wire x1="1.778" y1="0.508" x2="1.524" y2="0.508" width="0.1524" layer="51"/>
<wire x1="1.524" y1="0.508" x2="1.524" y2="0.762" width="0.1524" layer="51"/>
<wire x1="1.524" y1="0.762" x2="1.016" y2="0.762" width="0.1524" layer="51"/>
<wire x1="0.254" y1="-1.27" x2="2.286" y2="-1.27" width="0.1524" layer="21"/>
<wire x1="2.286" y1="-1.27" x2="2.54" y2="-1.016" width="0.1524" layer="21"/>
<wire x1="2.54" y1="-1.016" x2="2.794" y2="-1.27" width="0.1524" layer="21"/>
<wire x1="2.794" y1="-1.27" x2="4.826" y2="-1.27" width="0.1524" layer="21"/>
<wire x1="4.826" y1="-1.27" x2="5.08" y2="-1.016" width="0.1524" layer="21"/>
<wire x1="5.08" y1="-1.016" x2="5.334" y2="-1.27" width="0.1524" layer="21"/>
<wire x1="5.334" y1="1.27" x2="5.08" y2="1.016" width="0.1524" layer="21"/>
<wire x1="5.08" y1="1.016" x2="4.826" y2="1.27" width="0.1524" layer="21"/>
<wire x1="4.826" y1="1.27" x2="2.794" y2="1.27" width="0.1524" layer="21"/>
<wire x1="2.794" y1="1.27" x2="2.54" y2="1.016" width="0.1524" layer="21"/>
<wire x1="2.54" y1="1.016" x2="2.286" y2="1.27" width="0.1524" layer="21"/>
<wire x1="2.286" y1="1.27" x2="0.254" y2="1.27" width="0.1524" layer="21"/>
<wire x1="3.556" y1="0.762" x2="3.556" y2="0.508" width="0.1524" layer="51"/>
<wire x1="3.556" y1="0.508" x2="3.302" y2="0.508" width="0.1524" layer="51"/>
<wire x1="3.302" y1="0.508" x2="3.302" y2="-0.508" width="0.1524" layer="51"/>
<wire x1="3.302" y1="-0.508" x2="3.556" y2="-0.508" width="0.1524" layer="51"/>
<wire x1="3.556" y1="-0.508" x2="3.556" y2="-0.762" width="0.1524" layer="51"/>
<wire x1="3.556" y1="-0.762" x2="4.064" y2="-0.762" width="0.1524" layer="51"/>
<wire x1="4.064" y1="-0.762" x2="4.064" y2="-0.508" width="0.1524" layer="51"/>
<wire x1="4.064" y1="-0.508" x2="4.318" y2="-0.508" width="0.1524" layer="51"/>
<wire x1="4.318" y1="-0.508" x2="4.318" y2="0.508" width="0.1524" layer="51"/>
<wire x1="4.318" y1="0.508" x2="4.064" y2="0.508" width="0.1524" layer="51"/>
<wire x1="4.064" y1="0.508" x2="4.064" y2="0.762" width="0.1524" layer="51"/>
<wire x1="4.064" y1="0.762" x2="3.556" y2="0.762" width="0.1524" layer="51"/>
<wire x1="6.096" y1="0.762" x2="6.096" y2="0.508" width="0.1524" layer="51"/>
<wire x1="6.096" y1="0.508" x2="5.842" y2="0.508" width="0.1524" layer="51"/>
<wire x1="5.842" y1="0.508" x2="5.842" y2="-0.508" width="0.1524" layer="51"/>
<wire x1="5.842" y1="-0.508" x2="6.096" y2="-0.508" width="0.1524" layer="51"/>
<wire x1="6.096" y1="-0.508" x2="6.096" y2="-0.762" width="0.1524" layer="51"/>
<wire x1="6.096" y1="-0.762" x2="6.604" y2="-0.762" width="0.1524" layer="51"/>
<wire x1="6.604" y1="-0.762" x2="6.604" y2="-0.508" width="0.1524" layer="51"/>
<wire x1="6.604" y1="-0.508" x2="6.858" y2="-0.508" width="0.1524" layer="51"/>
<wire x1="6.858" y1="-0.508" x2="6.858" y2="0.508" width="0.1524" layer="51"/>
<wire x1="6.858" y1="0.508" x2="6.604" y2="0.508" width="0.1524" layer="51"/>
<wire x1="6.604" y1="0.508" x2="6.604" y2="0.762" width="0.1524" layer="51"/>
<wire x1="6.604" y1="0.762" x2="6.096" y2="0.762" width="0.1524" layer="51"/>
<wire x1="10.16" y1="1.27" x2="7.874" y2="1.27" width="0.1524" layer="21"/>
<wire x1="10.16" y1="-1.27" x2="10.16" y2="1.27" width="0.1524" layer="21"/>
<wire x1="7.874" y1="-1.27" x2="10.16" y2="-1.27" width="0.1524" layer="21"/>
<wire x1="7.62" y1="1.016" x2="7.366" y2="1.27" width="0.1524" layer="21"/>
<wire x1="7.874" y1="1.27" x2="7.62" y2="1.016" width="0.1524" layer="21"/>
<wire x1="7.366" y1="1.27" x2="5.334" y2="1.27" width="0.1524" layer="21"/>
<wire x1="7.62" y1="-1.016" x2="7.874" y2="-1.27" width="0.1524" layer="21"/>
<wire x1="7.366" y1="-1.27" x2="7.62" y2="-1.016" width="0.1524" layer="21"/>
<wire x1="5.334" y1="-1.27" x2="7.366" y2="-1.27" width="0.1524" layer="21"/>
<wire x1="8.636" y1="0.762" x2="8.636" y2="0.508" width="0.1524" layer="51"/>
<wire x1="8.636" y1="0.508" x2="8.382" y2="0.508" width="0.1524" layer="51"/>
<wire x1="8.382" y1="0.508" x2="8.382" y2="-0.508" width="0.1524" layer="51"/>
<wire x1="8.382" y1="-0.508" x2="8.636" y2="-0.508" width="0.1524" layer="51"/>
<wire x1="8.636" y1="-0.508" x2="8.636" y2="-0.762" width="0.1524" layer="51"/>
<wire x1="8.636" y1="-0.762" x2="9.144" y2="-0.762" width="0.1524" layer="51"/>
<wire x1="9.144" y1="-0.762" x2="9.144" y2="-0.508" width="0.1524" layer="51"/>
<wire x1="9.144" y1="-0.508" x2="9.398" y2="-0.508" width="0.1524" layer="51"/>
<wire x1="9.398" y1="-0.508" x2="9.398" y2="0.508" width="0.1524" layer="51"/>
<wire x1="9.398" y1="0.508" x2="9.144" y2="0.508" width="0.1524" layer="51"/>
<wire x1="9.144" y1="0.508" x2="9.144" y2="0.762" width="0.1524" layer="51"/>
<wire x1="9.144" y1="0.762" x2="8.636" y2="0.762" width="0.1524" layer="51"/>
<pad name="1" x="-8.89" y="0" drill="0.8128" shape="long" rot="R90"/>
<pad name="2" x="-6.35" y="0" drill="0.8128" shape="long" rot="R90"/>
<pad name="3" x="-3.81" y="0" drill="0.8128" shape="long" rot="R90"/>
<pad name="4" x="-1.27" y="0" drill="0.8128" shape="long" rot="R90"/>
<pad name="5" x="1.27" y="0" drill="0.8128" shape="long" rot="R90"/>
<pad name="6" x="3.81" y="0" drill="0.8128" shape="long" rot="R90"/>
<pad name="7" x="6.35" y="0" drill="0.8128" shape="long" rot="R90"/>
<pad name="8" x="8.89" y="0" drill="0.8128" shape="long" rot="R90"/>
<text x="-6.35" y="1.651" size="1.27" layer="25" ratio="10">&gt;NAME</text>
<text x="-9.398" y="1.524" size="1.27" layer="21" ratio="10">1</text>
<text x="-10.16" y="-2.921" size="1.27" layer="27" ratio="10">&gt;VALUE</text>
<text x="8.382" y="1.524" size="1.27" layer="21" ratio="10">8</text>
<rectangle x1="-9.017" y1="0.254" x2="-8.763" y2="0.762" layer="51"/>
<rectangle x1="-9.017" y1="-0.762" x2="-8.763" y2="-0.254" layer="51"/>
<rectangle x1="-6.477" y1="0.254" x2="-6.223" y2="0.762" layer="51"/>
<rectangle x1="-6.477" y1="-0.762" x2="-6.223" y2="-0.254" layer="51"/>
<rectangle x1="-3.937" y1="0.254" x2="-3.683" y2="0.762" layer="51"/>
<rectangle x1="-3.937" y1="-0.762" x2="-3.683" y2="-0.254" layer="51"/>
<rectangle x1="-1.397" y1="0.254" x2="-1.143" y2="0.762" layer="51"/>
<rectangle x1="-1.397" y1="-0.762" x2="-1.143" y2="-0.254" layer="51"/>
<rectangle x1="1.143" y1="0.254" x2="1.397" y2="0.762" layer="51"/>
<rectangle x1="1.143" y1="-0.762" x2="1.397" y2="-0.254" layer="51"/>
<rectangle x1="3.683" y1="0.254" x2="3.937" y2="0.762" layer="51"/>
<rectangle x1="3.683" y1="-0.762" x2="3.937" y2="-0.254" layer="51"/>
<rectangle x1="6.223" y1="0.254" x2="6.477" y2="0.762" layer="51"/>
<rectangle x1="6.223" y1="-0.762" x2="6.477" y2="-0.254" layer="51"/>
<rectangle x1="8.763" y1="0.254" x2="9.017" y2="0.762" layer="51"/>
<rectangle x1="8.763" y1="-0.762" x2="9.017" y2="-0.254" layer="51"/>
</package>
</packages>
<symbols>
<symbol name="FE08-1">
<wire x1="3.81" y1="-10.16" x2="-1.27" y2="-10.16" width="0.4064" layer="94"/>
<wire x1="1.905" y1="-1.905" x2="1.905" y2="-3.175" width="0.254" layer="94" curve="-180" cap="flat"/>
<wire x1="1.905" y1="-4.445" x2="1.905" y2="-5.715" width="0.254" layer="94" curve="-180" cap="flat"/>
<wire x1="1.905" y1="-6.985" x2="1.905" y2="-8.255" width="0.254" layer="94" curve="-180" cap="flat"/>
<wire x1="1.905" y1="3.175" x2="1.905" y2="1.905" width="0.254" layer="94" curve="-180" cap="flat"/>
<wire x1="1.905" y1="0.635" x2="1.905" y2="-0.635" width="0.254" layer="94" curve="-180" cap="flat"/>
<wire x1="1.905" y1="10.795" x2="1.905" y2="9.525" width="0.254" layer="94" curve="-180" cap="flat"/>
<wire x1="1.905" y1="8.255" x2="1.905" y2="6.985" width="0.254" layer="94" curve="-180" cap="flat"/>
<wire x1="1.905" y1="5.715" x2="1.905" y2="4.445" width="0.254" layer="94" curve="-180" cap="flat"/>
<wire x1="-1.27" y1="12.7" x2="-1.27" y2="-10.16" width="0.4064" layer="94"/>
<wire x1="3.81" y1="-10.16" x2="3.81" y2="12.7" width="0.4064" layer="94"/>
<wire x1="-1.27" y1="12.7" x2="3.81" y2="12.7" width="0.4064" layer="94"/>
<text x="-1.27" y="-12.7" size="1.778" layer="96">&gt;VALUE</text>
<text x="-1.27" y="13.462" size="1.778" layer="95">&gt;NAME</text>
<pin name="1" x="7.62" y="-7.62" visible="pad" length="middle" direction="pas" swaplevel="1" rot="R180"/>
<pin name="2" x="7.62" y="-5.08" visible="pad" length="middle" direction="pas" swaplevel="1" rot="R180"/>
<pin name="3" x="7.62" y="-2.54" visible="pad" length="middle" direction="pas" swaplevel="1" rot="R180"/>
<pin name="4" x="7.62" y="0" visible="pad" length="middle" direction="pas" swaplevel="1" rot="R180"/>
<pin name="5" x="7.62" y="2.54" visible="pad" length="middle" direction="pas" swaplevel="1" rot="R180"/>
<pin name="6" x="7.62" y="5.08" visible="pad" length="middle" direction="pas" swaplevel="1" rot="R180"/>
<pin name="7" x="7.62" y="7.62" visible="pad" length="middle" direction="pas" swaplevel="1" rot="R180"/>
<pin name="8" x="7.62" y="10.16" visible="pad" length="middle" direction="pas" swaplevel="1" rot="R180"/>
</symbol>
</symbols>
<devicesets>
<deviceset name="FE08-1" prefix="SV" uservalue="yes">
<description>&lt;b&gt;FEMALE HEADER&lt;/b&gt;</description>
<gates>
<gate name="G$1" symbol="FE08-1" x="0" y="0"/>
</gates>
<devices>
<device name="" package="FE08">
<connects>
<connect gate="G$1" pin="1" pad="1"/>
<connect gate="G$1" pin="2" pad="2"/>
<connect gate="G$1" pin="3" pad="3"/>
<connect gate="G$1" pin="4" pad="4"/>
<connect gate="G$1" pin="5" pad="5"/>
<connect gate="G$1" pin="6" pad="6"/>
<connect gate="G$1" pin="7" pad="7"/>
<connect gate="G$1" pin="8" pad="8"/>
</connects>
<technologies>
<technology name="">
<attribute name="MF" value="" constant="no"/>
<attribute name="MPN" value="" constant="no"/>
<attribute name="OC_FARNELL" value="unknown" constant="no"/>
<attribute name="OC_NEWARK" value="unknown" constant="no"/>
</technology>
</technologies>
</device>
</devices>
</deviceset>
</devicesets>
</library>
</libraries>
<attributes>
</attributes>
<variantdefs>
</variantdefs>
<classes>
<class number="0" name="default" width="0" drill="0">
</class>
</classes>
<parts>
<part name="U1" library="Texas Instruments_By_element14_Batch_1" deviceset="ADS1231ID" device=""/>
<part name="SV1" library="con-lsta" deviceset="FE08-1" device=""/>
<part name="SV2" library="con-lsta" deviceset="FE08-1" device=""/>
</parts>
<sheets>
<sheet>
<plain>
</plain>
<instances>
<instance part="U1" gate="A" x="40.64" y="40.64"/>
<instance part="SV1" gate="G$1" x="-17.78" y="38.1"/>
<instance part="SV2" gate="G$1" x="86.36" y="40.64" rot="R180"/>
</instances>
<busses>
</busses>
<nets>
<net name="DVDD" class="0">
<segment>
<pinref part="SV1" gate="G$1" pin="1"/>
<wire x1="-10.16" y1="30.48" x2="-2.54" y2="30.48" width="0.1524" layer="91"/>
<label x="-7.62" y="30.48" size="1.778" layer="95"/>
</segment>
<segment>
<pinref part="U1" gate="A" pin="DVDD"/>
<wire x1="17.78" y1="55.88" x2="12.7" y2="55.88" width="0.1524" layer="91"/>
</segment>
</net>
<net name="GND_2" class="0">
<segment>
<pinref part="SV1" gate="G$1" pin="2"/>
<wire x1="-10.16" y1="33.02" x2="-2.54" y2="33.02" width="0.1524" layer="91"/>
<label x="-7.62" y="33.02" size="1.778" layer="95"/>
</segment>
<segment>
<pinref part="U1" gate="A" pin="GND_2"/>
<wire x1="17.78" y1="17.78" x2="12.7" y2="17.78" width="0.1524" layer="91"/>
</segment>
</net>
<net name="CLKIN" class="0">
<segment>
<pinref part="SV1" gate="G$1" pin="3"/>
<wire x1="-10.16" y1="35.56" x2="-2.54" y2="35.56" width="0.1524" layer="91"/>
<label x="-7.62" y="35.56" size="1.778" layer="95"/>
</segment>
<segment>
<pinref part="U1" gate="A" pin="CLKIN"/>
<wire x1="17.78" y1="48.26" x2="12.7" y2="48.26" width="0.1524" layer="91"/>
</segment>
</net>
<net name="SPEED" class="0">
<segment>
<pinref part="SV1" gate="G$1" pin="4"/>
<wire x1="-10.16" y1="38.1" x2="-2.54" y2="38.1" width="0.1524" layer="91"/>
<label x="-7.62" y="38.1" size="1.778" layer="95"/>
</segment>
<segment>
<pinref part="U1" gate="A" pin="SPEED"/>
<wire x1="17.78" y1="38.1" x2="12.7" y2="38.1" width="0.1524" layer="91"/>
</segment>
</net>
<net name="CAP_2" class="0">
<segment>
<pinref part="SV1" gate="G$1" pin="5"/>
<wire x1="-10.16" y1="40.64" x2="-2.54" y2="40.64" width="0.1524" layer="91"/>
<label x="-7.62" y="40.64" size="1.778" layer="95"/>
</segment>
<segment>
<pinref part="U1" gate="A" pin="CAP_2"/>
<wire x1="17.78" y1="35.56" x2="12.7" y2="35.56" width="0.1524" layer="91"/>
</segment>
</net>
<net name="CAP" class="0">
<segment>
<pinref part="SV1" gate="G$1" pin="6"/>
<wire x1="-10.16" y1="43.18" x2="-2.54" y2="43.18" width="0.1524" layer="91"/>
<label x="-7.62" y="43.18" size="1.778" layer="95"/>
</segment>
<segment>
<pinref part="U1" gate="A" pin="CAP"/>
<wire x1="17.78" y1="33.02" x2="12.7" y2="33.02" width="0.1524" layer="91"/>
</segment>
</net>
<net name="AINP" class="0">
<segment>
<pinref part="SV1" gate="G$1" pin="7"/>
<wire x1="-10.16" y1="45.72" x2="-2.54" y2="45.72" width="0.1524" layer="91"/>
<label x="-7.62" y="45.72" size="1.778" layer="95"/>
</segment>
<segment>
<pinref part="U1" gate="A" pin="AINP"/>
<wire x1="17.78" y1="30.48" x2="12.7" y2="30.48" width="0.1524" layer="91"/>
</segment>
</net>
<net name="AINN" class="0">
<segment>
<pinref part="SV1" gate="G$1" pin="8"/>
<wire x1="-10.16" y1="48.26" x2="-2.54" y2="48.26" width="0.1524" layer="91"/>
<label x="-7.62" y="48.26" size="1.778" layer="95"/>
</segment>
<segment>
<pinref part="U1" gate="A" pin="AINN"/>
<wire x1="17.78" y1="27.94" x2="12.7" y2="27.94" width="0.1524" layer="91"/>
</segment>
</net>
<net name="VREFN" class="0">
<segment>
<pinref part="SV2" gate="G$1" pin="1"/>
<wire x1="78.74" y1="48.26" x2="73.66" y2="48.26" width="0.1524" layer="91"/>
<label x="88.9" y="48.26" size="1.778" layer="95"/>
</segment>
<segment>
<pinref part="U1" gate="A" pin="VREFN"/>
<wire x1="17.78" y1="22.86" x2="12.7" y2="22.86" width="0.1524" layer="91"/>
</segment>
</net>
<net name="VREFP" class="0">
<segment>
<pinref part="SV2" gate="G$1" pin="2"/>
<wire x1="78.74" y1="45.72" x2="73.66" y2="45.72" width="0.1524" layer="91"/>
<label x="88.9" y="45.72" size="1.778" layer="95"/>
</segment>
<segment>
<pinref part="U1" gate="A" pin="VREFP"/>
<wire x1="17.78" y1="25.4" x2="12.7" y2="25.4" width="0.1524" layer="91"/>
</segment>
</net>
<net name="GND" class="0">
<segment>
<pinref part="SV2" gate="G$1" pin="3"/>
<wire x1="78.74" y1="43.18" x2="73.66" y2="43.18" width="0.1524" layer="91"/>
<label x="88.9" y="43.18" size="1.778" layer="95"/>
</segment>
<segment>
<pinref part="U1" gate="A" pin="GND"/>
<wire x1="17.78" y1="15.24" x2="12.7" y2="15.24" width="0.1524" layer="91"/>
</segment>
</net>
<net name="PSW" class="0">
<segment>
<pinref part="SV2" gate="G$1" pin="4"/>
<wire x1="78.74" y1="40.64" x2="73.66" y2="40.64" width="0.1524" layer="91"/>
<label x="88.9" y="40.64" size="1.778" layer="95"/>
</segment>
<segment>
<pinref part="U1" gate="A" pin="PSW"/>
<wire x1="17.78" y1="43.18" x2="12.7" y2="43.18" width="0.1524" layer="91"/>
</segment>
</net>
<net name="AVDD" class="0">
<segment>
<pinref part="SV2" gate="G$1" pin="5"/>
<wire x1="78.74" y1="38.1" x2="73.66" y2="38.1" width="0.1524" layer="91"/>
<label x="88.9" y="38.1" size="1.778" layer="95"/>
</segment>
<segment>
<pinref part="U1" gate="A" pin="AVDD"/>
<wire x1="17.78" y1="58.42" x2="12.7" y2="58.42" width="0.1524" layer="91"/>
</segment>
</net>
<net name="~PDWN" class="0">
<segment>
<pinref part="SV2" gate="G$1" pin="6"/>
<wire x1="78.74" y1="35.56" x2="73.66" y2="35.56" width="0.1524" layer="91"/>
<label x="88.9" y="35.56" size="1.778" layer="95"/>
</segment>
<segment>
<pinref part="U1" gate="A" pin="~PDWN"/>
<wire x1="17.78" y1="40.64" x2="12.7" y2="40.64" width="0.1524" layer="91"/>
</segment>
</net>
<net name="SCLK" class="0">
<segment>
<pinref part="SV2" gate="G$1" pin="7"/>
<wire x1="78.74" y1="33.02" x2="73.66" y2="33.02" width="0.1524" layer="91"/>
<label x="88.9" y="33.02" size="1.778" layer="95"/>
</segment>
<segment>
<pinref part="U1" gate="A" pin="SCLK"/>
<wire x1="17.78" y1="50.8" x2="12.7" y2="50.8" width="0.1524" layer="91"/>
</segment>
</net>
<net name="~DRDY/DOUT" class="0">
<segment>
<pinref part="SV2" gate="G$1" pin="8"/>
<wire x1="78.74" y1="30.48" x2="73.66" y2="30.48" width="0.1524" layer="91"/>
<label x="88.9" y="30.48" size="1.778" layer="95"/>
</segment>
<segment>
<pinref part="U1" gate="A" pin="~DRDY/DOUT"/>
<wire x1="63.5" y1="58.42" x2="68.58" y2="58.42" width="0.1524" layer="91"/>
</segment>
</net>
</nets>
</sheet>
</sheets>
</schematic>
</drawing>
</eagle>
