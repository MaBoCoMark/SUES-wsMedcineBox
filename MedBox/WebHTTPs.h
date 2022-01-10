#include "DelayPWM.h"
#include "WebIncludes.h"
#include "defineS.h"
#define LED_BUILTIN 22

WiFiMulti wifiMulti;
WebServer esp8266_server(80);
/* <!-- WebDevVar --> */
String testCode = "<!DOCTYPE html><meta charset=\"utf-8\"/><title>Test</title><h2>Testing</h2>";
const char *ssid = "a8266";
const char *password = "12345678";
bool internetConnected = 0;
bool internetConfirmation = 0;
bool timeModified = 0;
bool offlineMode = 0;
/* <!-- WebUserVar --> */
char capAvaliable[17] = {1};
char capNote[17] = {0};
String Cap00name = "0";
String Cap01name = "1";
String Cap02name = "2";
String Cap03name = "3";
String Cap04name = "4";
String Cap05name = "5";
String Cap06name = "6";
String Cap07name = "7";
String Cap08name = "8";
String Cap09name = "9";
String Cap10name = "10";
String Cap11name = "11";
String Cap12name = "12";
String Cap13name = "13";
String Cap14name = "14";
String Cap15name = "15";
String Cap16name = "16";
String Cap17name = "17";
String userInputTime = "time";
String userInputNote = "note";
String theLog = "";
/* <!-- WebFuncVar --> */
String pendingCap = "25";
/* <!-- GlobalUsageVar --> */
int webTime[5]={2022,1,31,23,59};
bool pending = 0;
/* <!-- VarWriteFunc --> */
void yySet(int newYear){webTime[0]=newYear;}
void mmSet(int newMonth){webTime[1]=newMonth;}
void ddSet(int newDay){webTime[2]=newDay;}
void hhSet(int newHour){webTime[3]=newHour;}
void minSet(int newMinute){webTime[4]=newMinute;}
void clearRequests()
{
    pending = 0;
    pendingCap = "25";
    userInputTime = "time";
}
void clearPending(){pending = 0;}
/* <!-- VarReadFunc --> */
int yyGet(){return webTime[0];}
int mmGet(){return webTime[1];}
int ddGet(){return webTime[2];}
int hhGet(){return webTime[3];}
int minGet(){return webTime[4];}
int ifRequesets(){if(pending){return 1;}else{return 0;}}
String getPendingTime(){return userInputTime;}
String getPendingNote(){return userInputNote;}
int getPendingCap(){return pendingCap.toInt();}
/* <!-- UsefulFuncs --> */
void capInit()
{
    Cap00name = "0";
    Cap01name = "1";
    Cap02name = "2";
    Cap03name = "3";
    Cap04name = "4";
    Cap05name = "5";
    Cap06name = "6";
    Cap07name = "7";
    Cap08name = "8";
    Cap09name = "9";
    Cap10name = "10";
    Cap11name = "11";
    Cap12name = "12";
    Cap13name = "13";
    Cap14name = "14";
    Cap15name = "15";
    Cap16name = "16";
    Cap17name = "17";
}
void addLog(bool isPut = 0)
{
    theLog += "<tr><td>";
    theLog += (String(webTime[0])+"-"+String(webTime[1])+"-"+String(webTime[2])+" "+String(webTime[3])+":"+String(webTime[4])+"</td><td align=\"center\">");
    if(isPut){theLog += "Put</td><td>Capsule ";}
    else{theLog += "Get</td><td>Capsule ";}
    theLog += pendingCap;
    theLog += "</td><td>";
    switch(getPendingCap())
    {
        case 0: theLog += Cap00name;break;
        case 1: theLog += Cap01name;break;
        case 2: theLog += Cap02name;break;
        case 3: theLog += Cap03name;break;
        case 4: theLog += Cap04name;break;
        case 5: theLog += Cap05name;break;
        case 6: theLog += Cap06name;break;
        case 7: theLog += Cap07name;break;
        case 8: theLog += Cap08name;break;
        case 9: theLog += Cap09name;break;
        case 10: theLog += Cap10name ;break;
        case 11: theLog += Cap11name ;break;
        case 12: theLog += Cap12name ;break;
        case 13: theLog += Cap13name ;break;
        case 14: theLog += Cap14name ;break;
        case 15: theLog += Cap15name ;break;
        case 16: theLog += Cap16name ;break;
        case 17: theLog += Cap17name ;break;
        default: break;
    }
    theLog += "</td></tr>";
}
/* <!-- PageStr --> */
String sendRoot()
{
    String htmlCode = "<!DOCTYPE html><meta charset=\"utf-8\"/><title>MedBox</title><h1>Welcome</h1>";
    if(1 == offlineMode)
    {   htmlCode+= "<meta http-equiv=\"refresh\"content=\"2;url=./Stat\">";  }
    else if(0 == internetConnected)
    {   htmlCode+= "<meta http-equiv=\"refresh\"content=\"2;url=./WLANconnect\">";  }
    else if(0 == internetConfirmation)
    {   htmlCode+= "<meta http-equiv=\"refresh\"content=\"2;url=./WLANconnect/connecting/confirm\">";  }
    else if(0 == timeModified)
    {   htmlCode+= "<meta http-equiv=\"refresh\"content=\"2;url=./TimeSet\">";  }
    else
    {   htmlCode+= "<meta http-equiv=\"refresh\"content=\"2;url=./Stat\">";  }
    return htmlCode;
}
String sendDev()//
{
    String htmlCode = "";
    return htmlCode;
}
String sendStat()
{
    String htmlCode = "<!DOCTYPE html><meta charset=\"utf-8\"/><title>MedBox</title><h1>MedBox Stats</h1>";
    if(offlineMode && !(internetConnected) ){htmlCode+="<h5>Offline Mode</h5>";}
    htmlCode += "<a href=\"../TimeSet\"><button>Time Settings</button></a><a href=\"../WLANconnect\"><button>WiFi Settings</button></a><table><tbody>";
    htmlCode += "<tr><td>6</td><td align=\"center\">";
    htmlCode += Cap15name;
    if(0 == capAvaliable[15])
    {   if(0 == capNote[15])
        {
            htmlCode += "<br><a href=\"./Note?Cap=15\"><button disabled=\"true\">Note</button></a>";
        }
        else{htmlCode += "<br><a href=\"./Note?Cap=15\"><button>Note</button></a>";}
    }
    htmlCode += "</td><td align=\"center\">";
    htmlCode += Cap16name;
    if(0 == capAvaliable[16])
    {   if(0 == capNote[16])
        {
            htmlCode += "<br><a href=\"./Note?Cap=16\"><button disabled=\"true\">Note</button></a>";
        }
        else{htmlCode += "<br><a href=\"./Note?Cap=16\"><button>Note</button></a>";}
    }
    htmlCode += "</td><td align=\"center\">";
    htmlCode += Cap17name;
    if(0 == capAvaliable[17])
    {   if(0 == capNote[17])
        {
            htmlCode += "<br><a href=\"./Note?Cap=17\"><button disabled=\"true\">Note</button></a>";
        }
        else{htmlCode += "<br><a href=\"./Note?Cap=17\"><button>Note</button></a>";}
    }
    htmlCode += "</td><td align=\"center\"></tr>";
    htmlCode += "<tr><td>5</td><td align=\"center\">";
    htmlCode += Cap12name;
    if(0 == capAvaliable[12])
    {   if(0 == capNote[12])
        {
            htmlCode += "<br><a href=\"./Note?Cap=12\"><button disabled=\"true\">Note</button></a>";
        }
        else{htmlCode += "<br><a href=\"./Note?Cap=12\"><button>Note</button></a>";}
    }
    htmlCode += "</td><td align=\"center\">";
    htmlCode += Cap13name;
    if(0 == capAvaliable[13])
    {   if(0 == capNote[13])
        {
            htmlCode += "<br><a href=\"./Note?Cap=13\"><button disabled=\"true\">Note</button></a>";
        }
        else{htmlCode += "<br><a href=\"./Note?Cap=13\"><button>Note</button></a>";}
    }
    htmlCode += "</td><td align=\"center\">";
    htmlCode += Cap14name;
    if(0 == capAvaliable[14])
    {   if(0 == capNote[14])
        {
            htmlCode += "<br><a href=\"./Note?Cap=14\"><button disabled=\"true\">Note</button></a>";
        }
        else{htmlCode += "<br><a href=\"./Note?Cap=14\"><button>Note</button></a>";}
    }
    htmlCode += "</td><td align=\"center\"></tr>";
    htmlCode += "<tr><td>4</td><td align=\"center\">";
    htmlCode += Cap09name;
    if(0 == capAvaliable[9])
    {   if(0 == capNote[9])
        {
            htmlCode += "<br><a href=\"./Note?Cap=9\"><button disabled=\"true\">Note</button></a>";
        }
        else{htmlCode += "<br><a href=\"./Note?Cap=9\"><button>Note</button></a>";}
    }
    htmlCode += "</td><td align=\"center\">";
    htmlCode += Cap10name;
    if(0 == capAvaliable[10])
    {   if(0 == capNote[10])
        {
            htmlCode += "<br><a href=\"./Note?Cap=10\"><button disabled=\"true\">Note</button></a>";
        }
        else{htmlCode += "<br><a href=\"./Note?Cap=10\"><button>Note</button></a>";}
    }
    htmlCode += "</td><td align=\"center\">";
    htmlCode += Cap11name;
    if(0 == capAvaliable[11])
    {   if(0 == capNote[11])
        {
            htmlCode += "<br><a href=\"./Note?Cap=11\"><button disabled=\"true\">Note</button></a>";
        }
        else{htmlCode += "<br><a href=\"./Note?Cap=11\"><button>Note</button></a>";}
    }
    htmlCode += "</td><td align=\"center\"></tr>";
    htmlCode += "<tr><td>3</td><td align=\"center\">";
    htmlCode += Cap06name;
    if(0 == capAvaliable[6])
    {   if(0 == capNote[6])
        {
            htmlCode += "<br><a href=\"./Note?Cap=6\"><button disabled=\"true\">Note</button></a>";
        }
        else{htmlCode += "<br><a href=\"./Note?Cap=6\"><button>Note</button></a>";}
    }
    htmlCode += "</td><td align=\"center\">";
    htmlCode += Cap07name;
    if(0 == capAvaliable[7])
    {   if(0 == capNote[7])
        {
            htmlCode += "<br><a href=\"./Note?Cap=7\"><button disabled=\"true\">Note</button></a>";
        }
        else{htmlCode += "<br><a href=\"./Note?Cap=7\"><button>Note</button></a>";}
    }
    htmlCode += "</td><td align=\"center\">";
    htmlCode += Cap08name;
    if(0 == capAvaliable[8])
    {   if(0 == capNote[8])
        {
            htmlCode += "<br><a href=\"./Note?Cap=8\"><button disabled=\"true\">Note</button></a>";
        }
        else{htmlCode += "<br><a href=\"./Note?Cap=8\"><button>Note</button></a>";}
    }
    htmlCode += "</td><td align=\"center\"></tr>";
    htmlCode += "<tr><td>2</td><td align=\"center\">";
    htmlCode += Cap03name;
    if(0 == capAvaliable[3])
    {   if(0 == capNote[3])
        {
            htmlCode += "<br><a href=\"./Note?Cap=3\"><button disabled=\"true\">Note</button></a>";
        }
        else{htmlCode += "<br><a href=\"./Note?Cap=3\"><button>Note</button></a>";}
    }
    htmlCode += "</td><td align=\"center\">";
    htmlCode += Cap04name;
    if(0 == capAvaliable[4])
    {   if(0 == capNote[4])
        {
            htmlCode += "<br><a href=\"./Note?Cap=4\"><button disabled=\"true\">Note</button></a>";
        }
        else{htmlCode += "<br><a href=\"./Note?Cap=4\"><button>Note</button></a>";}
    }
    htmlCode += "</td><td align=\"center\">";
    htmlCode += Cap05name;
    if(0 == capAvaliable[5])
    {   if(0 == capNote[5])
        {
            htmlCode += "<br><a href=\"./Note?Cap=5\"><button disabled=\"true\">Note</button></a>";
        }
        else{htmlCode += "<br><a href=\"./Note?Cap=5\"><button>Note</button></a>";}
    }
    htmlCode += "</td><td align=\"center\"></tr>";
    htmlCode += "<tr><td>1</td><td align=\"center\">";
    htmlCode += Cap00name;
    if(0 == capAvaliable[0])
    {   if(0 == capNote[0])
        {
            htmlCode += "<br><a href=\"./Note?Cap=0\"><button disabled=\"true\">Note</button></a>";
        }
        else{htmlCode += "<br><a href=\"./Note?Cap=0\"><button>Note</button></a>";}
    }
    htmlCode += "</td><td align=\"center\">";
    htmlCode += Cap01name;
    if(0 == capAvaliable[1])
    {   if(0 == capNote[1])
        {
            htmlCode += "<br><a href=\"./Note?Cap=1\"><button disabled=\"true\">Note</button></a>";
        }
        else{htmlCode += "<br><a href=\"./Note?Cap=1\"><button>Note</button></a>";}
    }
    htmlCode += "</td><td align=\"center\">";
    htmlCode += Cap02name;
    if(0 == capAvaliable[2])
    {   if(0 == capNote[2])
        {
            htmlCode += "<br><a href=\"./Note?Cap=2\"><button disabled=\"true\">Note</button></a>";
        }
        else{htmlCode += "<br><a href=\"./Note?Cap=2\"><button>Note</button></a>";}
    }
    htmlCode += "</td></tr></tbody><thead><tr><th>F</th><th align=\"center\">Left</th><th align=\"center\">Mid</th><th align=\"center\">Right</th><th><form action=\"./manage\"method=\"get\"><input type=\"submit\"value=\"Manage\"></form></th></tr></thead></table>";
    htmlCode += "<form action=\"./info\" method=\"get\"><input type=\"submit\" value=\"info\"></form>";
    htmlCode += "<form action=\"./log\" method=\"get\"><input type=\"submit\" value=\"log\"></form>";
    return htmlCode;
}
String sendInfo()//
{
    String htmlCode = "";
    return htmlCode;
}
String sendDevInfo()//
{
    String htmlCode = "";
    return htmlCode;
}
String sendLog()
{
    String htmlCode = "<!DOCTYPE html><meta charset=\"utf-8\"/><title>MedBox</title><h1>Logs</h1><table><thead><tr><th>Time(24h format)</th><th align=\"center\">Operation</th><th>Target</th><th>Description</th><th>Note</th></tr></thead><tbody>";
    htmlCode += theLog;
    htmlCode += "</tbody></table><form action=\"Stat\"method=\"get\"><input type=\"submit\"value=\"Back\"></form>";
    return htmlCode;
}
String sendManage()
{
    String htmlCode = "<!DOCTYPE html><meta charset=\"utf-8\"/><title>MedBox</title><h1>Capsule Manager</h1></a><table><tbody>";
    htmlCode += "<tr><td>6</td><td align=\"center\">";
    htmlCode += Cap15name;
    if(capAvaliable[15])
    {
        htmlCode += "<br><a href=\"./Get?Cap=15\"><button disabled=\"true\">Get</button></a><a href=\"./Put?Cap=15\"><button>Put</button></a>";
    }
    else
    {
        htmlCode += "<br><a href=\"./Get?Cap=15\"><button>Get</button></a><a href=\"./Put?Cap=15\"><button disabled=\"true\">Put</button></a>";
    }
    htmlCode += "</td><td align=\"center\">";
    htmlCode += Cap16name;
    if(capAvaliable[16])
    {
        htmlCode += "<br><a href=\"./Get?Cap=16\"><button disabled=\"true\">Get</button></a><a href=\"./Put?Cap=16\"><button>Put</button></a>";
    }
    else
    {
        htmlCode += "<br><a href=\"./Get?Cap=16\"><button>Get</button></a><a href=\"./Put?Cap=16\"><button disabled=\"true\">Put</button></a>";
    }
    htmlCode += "</td><td align=\"center\">";
    htmlCode += Cap17name;
    if(capAvaliable[17])
    {
        htmlCode += "<br><a href=\"./Get?Cap=17\"><button disabled=\"true\">Get</button></a><a href=\"./Put?Cap=17\"><button>Put</button></a>";
    }
    else
    {
        htmlCode += "<br><a href=\"./Get?Cap=17\"><button>Get</button></a><a href=\"./Put?Cap=17\"><button disabled=\"true\">Put</button></a>";
    }
    htmlCode += "</td><td align=\"center\"></tr>";
    htmlCode += "<tr><td>5</td><td align=\"center\">";
    htmlCode += Cap12name;
    if(capAvaliable[12])
    {
        htmlCode += "<br><a href=\"./Get?Cap=12\"><button disabled=\"true\">Get</button></a><a href=\"./Put?Cap=12\"><button>Put</button></a>";
    }
    else
    {
        htmlCode += "<br><a href=\"./Get?Cap=12\"><button>Get</button></a><a href=\"./Put?Cap=12\"><button disabled=\"true\">Put</button></a>";
    }
    htmlCode += "</td><td align=\"center\">";
    htmlCode += Cap13name;
    if(capAvaliable[13])
    {
        htmlCode += "<br><a href=\"./Get?Cap=13\"><button disabled=\"true\">Get</button></a><a href=\"./Put?Cap=13\"><button>Put</button></a>";
    }
    else
    {
        htmlCode += "<br><a href=\"./Get?Cap=13\"><button>Get</button></a><a href=\"./Put?Cap=13\"><button disabled=\"true\">Put</button></a>";
    }
    htmlCode += "</td><td align=\"center\">";
    htmlCode += Cap14name;
    if(capAvaliable[14])
    {
        htmlCode += "<br><a href=\"./Get?Cap=14\"><button disabled=\"true\">Get</button></a><a href=\"./Put?Cap=14\"><button>Put</button></a>";
    }
    else
    {
        htmlCode += "<br><a href=\"./Get?Cap=14\"><button>Get</button></a><a href=\"./Put?Cap=14\"><button disabled=\"true\">Put</button></a>";
    }
    htmlCode += "</td><td align=\"center\"></tr>";
    htmlCode += "<tr><td>4</td><td align=\"center\">";
    htmlCode += Cap09name;
    if(capAvaliable[9])
    {
        htmlCode += "<br><a href=\"./Get?Cap=9\"><button disabled=\"true\">Get</button></a><a href=\"./Put?Cap=9\"><button>Put</button></a>";
    }
    else
    {
        htmlCode += "<br><a href=\"./Get?Cap=9\"><button>Get</button></a><a href=\"./Put?Cap=9\"><button disabled=\"true\">Put</button></a>";
    }
    htmlCode += "</td><td align=\"center\">";
    htmlCode += Cap10name;
    if(capAvaliable[10])
    {
        htmlCode += "<br><a href=\"./Get?Cap=10\"><button disabled=\"true\">Get</button></a><a href=\"./Put?Cap=10\"><button>Put</button></a>";
    }
    else
    {
        htmlCode += "<br><a href=\"./Get?Cap=10\"><button>Get</button></a><a href=\"./Put?Cap=10\"><button disabled=\"true\">Put</button></a>";
    }
    htmlCode += "</td><td align=\"center\">";
    htmlCode += Cap11name;
    if(capAvaliable[11])
    {
        htmlCode += "<br><a href=\"./Get?Cap=11\"><button disabled=\"true\">Get</button></a><a href=\"./Put?Cap=11\"><button>Put</button></a>";
    }
    else
    {
        htmlCode += "<br><a href=\"./Get?Cap=11\"><button>Get</button></a><a href=\"./Put?Cap=11\"><button disabled=\"true\">Put</button></a>";
    }
    htmlCode += "</td><td align=\"center\"></tr>";
    htmlCode += "<tr><td>3</td><td align=\"center\">";
    htmlCode += Cap06name;
    if(capAvaliable[6])
    {
        htmlCode += "<br><a href=\"./Get?Cap=6\"><button disabled=\"true\">Get</button></a><a href=\"./Put?Cap=6\"><button>Put</button></a>";
    }
    else
    {
        htmlCode += "<br><a href=\"./Get?Cap=6\"><button>Get</button></a><a href=\"./Put?Cap=6\"><button disabled=\"true\">Put</button></a>";
    }
    htmlCode += "</td><td align=\"center\">";
    htmlCode += Cap07name;
    if(capAvaliable[7])
    {
        htmlCode += "<br><a href=\"./Get?Cap=7\"><button disabled=\"true\">Get</button></a><a href=\"./Put?Cap=7\"><button>Put</button></a>";
    }
    else
    {
        htmlCode += "<br><a href=\"./Get?Cap=7\"><button>Get</button></a><a href=\"./Put?Cap=7\"><button disabled=\"true\">Put</button></a>";
    }
    htmlCode += "</td><td align=\"center\">";
    htmlCode += Cap08name;
    if(capAvaliable[8])
    {
        htmlCode += "<br><a href=\"./Get?Cap=8\"><button disabled=\"true\">Get</button></a><a href=\"./Put?Cap=8\"><button>Put</button></a>";
    }
    else
    {
        htmlCode += "<br><a href=\"./Get?Cap=8\"><button>Get</button></a><a href=\"./Put?Cap=8\"><button disabled=\"true\">Put</button></a>";
    }
    htmlCode += "</td><td align=\"center\"></tr>";
    htmlCode += "<tr><td>2</td><td align=\"center\">";
    htmlCode += Cap03name;
    if(capAvaliable[3])
    {
        htmlCode += "<br><a href=\"./Get?Cap=3\"><button disabled=\"true\">Get</button></a><a href=\"./Put?Cap=3\"><button>Put</button></a>";
    }
    else
    {
        htmlCode += "<br><a href=\"./Get?Cap=3\"><button>Get</button></a><a href=\"./Put?Cap=3\"><button disabled=\"true\">Put</button></a>";
    }
    htmlCode += "</td><td align=\"center\">";
    htmlCode += Cap04name;
    if(capAvaliable[4])
     {
        htmlCode += "<br><a href=\"./Get?Cap=4\"><button disabled=\"true\">Get</button></a><a href=\"./Put?Cap=4\"><button>Put</button></a>";
    }
    else
    {
        htmlCode += "<br><a href=\"./Get?Cap=4\"><button>Get</button></a><a href=\"./Put?Cap=4\"><button disabled=\"true\">Put</button></a>";
    }
    htmlCode += "</td><td align=\"center\">";
    htmlCode += Cap05name;
    if(capAvaliable[5])
    {
        htmlCode += "<br><a href=\"./Get?Cap=5\"><button disabled=\"true\">Get</button></a><a href=\"./Put?Cap=5\"><button>Put</button></a>";
    }
    else
    {
        htmlCode += "<br><a href=\"./Get?Cap=5\"><button>Get</button></a><a href=\"./Put?Cap=5\"><button disabled=\"true\">Put</button></a>";
    }
    htmlCode += "</td><td align=\"center\"></tr>";
    htmlCode += "<tr><td>1</td><td align=\"center\">";
    htmlCode += Cap00name;
    if(capAvaliable[0])
    {
        htmlCode += "<br><a href=\"./Get?Cap=0\"><button disabled=\"true\">Get</button></a><a href=\"./Put?Cap=0\"><button>Put</button></a>";
    }
    else
    {
        htmlCode += "<br><a href=\"./Get?Cap=0\"><button>Get</button></a><a href=\"./Put?Cap=0\"><button disabled=\"true\">Put</button></a>";
    }
    htmlCode += "</td><td align=\"center\">";
    htmlCode += Cap01name;
    if(capAvaliable[1])
    {
        htmlCode += "<br><a href=\"./Get?Cap=1\"><button disabled=\"true\">Get</button></a><a href=\"./Put?Cap=1\"><button>Put</button></a>";
    }
    else
    {
        htmlCode += "<br><a href=\"./Get?Cap=1\"><button>Get</button></a><a href=\"./Put?Cap=1\"><button disabled=\"true\">Put</button></a>";
    }
    htmlCode += "</td><td align=\"center\">";
    htmlCode += Cap02name;
    if(capAvaliable[2])
    {
        htmlCode += "<br><a href=\"./Get?Cap=2\"><button disabled=\"true\">Get</button></a><a href=\"./Put?Cap=2\"><button>Put</button></a>";
    }
    else
    {
        htmlCode += "<br><a href=\"./Get?Cap=2\"><button>Get</button></a><a href=\"./Put?Cap=2\"><button disabled=\"true\">Put</button></a>";
    }
    htmlCode += "</td></tr></tbody><thead><tr><th>F</th><th align=\"center\">Left</th><th align=\"center\">Mid</th><th align=\"center\">Right</th><th><form action=\"Stat\" method=\"get\"><input type=\"submit\" value=\"Back\"></form></th></tr></thead></table>";
    return htmlCode;
}
String sendGet()
{
    String htmlCode = "<!DOCTYPE html><meta charset=\"utf-8\"/><title>MedBox</title><h1>Pushing Out Capsule</h1><h3>Click button after reaching the Capsule</h3><form action=\"manage\"method=\"get\"><input type=\"submit\"value=\"Back\"></form>";
    return htmlCode;
}
String sendPut()
{
    String htmlCode = "<!DOCTYPE html><meta charset=\"utf-8\"/><title>MedBox</title><h1>Insert info for Capsule ";
    htmlCode += pendingCap;
    htmlCode += "</h1><br><form action=\"manage\"method=\"get\"><input type=\"submit\"value=\"Back\"></form><br><form action=\"./infoInsert\"method=\"get\"><input type=\"text\"name=\"name\"value=\"name\"><br><input type=\"text\"name=\"alerttime\"value=\"2022-1-9 17:01\"><br><input type=\"checkbox\"name=\"ifNote\"value=\"1\"><input type=\"text\"name=\"note\"value=\"note\"><br><input type=\"submit\"value=\"Submit\"></form>";
    return htmlCode;
}
String sendNote()
{
    String htmlCode = "<!DOCTYPE html><meta charset=\"utf-8\"/><title>MedBox</title><h1>Note of Capsule ";
    htmlCode += pendingCap;
    htmlCode += "</h1><h4></h4>";
    htmlCode += esp8266_server.arg("Cap");
    htmlCode += "</h4><br><form action=\"Stat\"method=\"get\"><input type=\"submit\"value=\"Back\"></form>";
    return htmlCode;
}
String sendInfoInsert()
{
    String htmlCode = "<!DOCTYPE html><meta charset=\"utf-8\"/><title>WS MedBox</title><h1>Data Stored!</h1><meta http-equiv=\"refresh\"content=\"2;url=/manage\">";
    return htmlCode;
}
String sendTimeSet()
{
    String htmlCode = "<!DOCTYPE html><meta charset=\"utf-8\"/><title>Box Startup Configuration</title><h1>Setup Configuration</h1><h3>I need current time↓</h4><form action=\"./SetDone\"method=\"get\">";
    htmlCode += "<input type=\"text\" name=\"yy\" value=\"年\"><br>";
    htmlCode += "<input type=\"text\" name=\"mm\" value=\"月\"><br>";
    htmlCode += "<input type=\"text\" name=\"dd\" value=\"日\"><br>";
    htmlCode += "<input type=\"text\" name=\"hh\" value=\"23\"><br>";
    htmlCode += "<input type=\"text\" name=\"min\" value=\"59\"><br>";
    htmlCode += "<br><input type=\"submit\"value=\"Set\"></form>";
    return htmlCode;
}
String sendSetDone()
{
    String htmlCode = "<!DOCTYPE html><meta charset=\"utf-8\"/><title>MedBox</title><h1>Done!</h1><meta http-equiv=\"refresh\"content=\"2;url=../../Stat\">";
    return htmlCode;
}
String sendWLANconnect()
{
    String htmlCode = "<!DOCTYPE html><meta charset=\"utf-8\"/>";
            htmlCode +="<title>Internet Settings</title>";     
            htmlCode +="<h4>Type your wifi SSID and password down below ↓</h4>";
            htmlCode +="<form action=\"./Trying\" method=\"get\">";
            htmlCode +="<input type=\"text\" name=\"ssid\" value=\"SSID\"><br>";
            htmlCode +="<input type=\"password\" name=\"password\" value=\"P@ssW0rd\"><br>";
            htmlCode +="<input type=\"submit\" value=\"Let's go have a try\"></form>";
            htmlCode +="<br><h5>But<a href=\"./offline\">I have no Internet Connection!</a></h5>";
          return htmlCode;
}
String sendTrying()
{
    String htmlCode = "<!DOCTYPE html><meta charset=\"utf-8\"/>";
    htmlCode +="<title>WLAN Connecting...</title>";
    htmlCode +="<h1>Connecting...</h1><h5>Click ↓ when start to blink</h5>";
    htmlCode +="<a href=\"/connected\"><button>BACK</button>";
    htmlCode +="<h5>Click ↑ when start to blink</h5>";
    return htmlCode;
}
String sendConnected()
{
    String htmlCode = "<!DOCTYPE html><meta charset=\"utf-8\"/>";
          htmlCode +="<title>Easy2Use WiFi Stats</title>";
          htmlCode +="<h2>Connected to : ";
          htmlCode +=WiFi.SSID();
          htmlCode +=" as [";
          htmlCode +=WiFi.localIP().toString();
          htmlCode +="] </h2>"; 
          if(0 == internetConfirmation)
          {
              htmlCode += "<h3>Please Copy the IP address then click</h3>";
              htmlCode +="<form action=\"./confirm\" method=\"get\"><input type=\"submit\" value=\"Confirm\"></form>";
          }
    return htmlCode;
}
String sendConfirm()
{
    String htmlCode = "<!DOCTYPE html><meta charset=\"utf-8\"/><title>Redirecting...</title><h1>Redirecting...</h1><meta http-equiv=\"refresh\"content=\"2;url=../../../\">";
    return htmlCode;
}
String sendOffline()
{
    String htmlCode = "<!DOCTYPE html><meta charset=\"utf-8\"/><title>Offline Mode</title><h1>Warning!</h1><h3>In offline mode,you will LOST these features:</h3><h5>Online Stats</h5><h5>Online Settings</h5><meta http-equiv=\"refresh\"content=\"3;url=../../Stat\">";
    return htmlCode;
}
String sendPending()
{
    String htmlCode = "<!DOCTYPE html><meta charset=\"utf-8\"/><title>Request Pending...</title><h1>Request Pending...</h1><h4>You could do nothing right now:(</h4><meta http-equiv='refresh'content='2'/>";
    return htmlCode;
}
/* <!-- HandelFunc --> */
void handleRoot()
{
    if(pending){esp8266_server.send(200, "text/html",sendPending());}
    else
    {
        esp8266_server.send(200, "text/html",sendRoot());
    }
}
void handleDev()//
{
    esp8266_server.send(200, "text/html",sendDev());
}
void handleStat()
{
    if(pending){esp8266_server.send(200, "text/html",sendPending());}
    else
    {
        esp8266_server.send(200, "text/html",sendStat());
    }
}
void handleInfo()//
{
    if(pending){esp8266_server.send(200, "text/html",sendPending());}
    else
    {
        esp8266_server.send(200, "text/html",testCode);
    }
}
void handleDevInfo()//
{
    if(pending){esp8266_server.send(200, "text/html",sendPending());}
    else
    {
        esp8266_server.send(200, "text/html",testCode);
    }
}
void handleLog()
{
    if(pending){esp8266_server.send(200, "text/html",sendPending());}
    else
    {
        esp8266_server.send(200, "text/html",sendLog());
    }
}
void handleManage()
{
    if(pending){esp8266_server.send(200, "text/html",sendPending());}
    else
    {
        esp8266_server.send(200, "text/html",sendManage());
    }
}
void handleGet()
{
    if(pending){esp8266_server.send(200, "text/html",sendPending());}
    else
    {
        esp8266_server.send(200, "text/html",sendGet());
        pendingCap = esp8266_server.arg("Cap");
        pending = 1;
        switch(getPendingCap())
        {
            case 0: Cap00name = "0";break;
            case 1: Cap01name = "1";break;
            case 2: Cap02name = "2";break;
            case 3: Cap03name = "3";break;
            case 4: Cap04name = "4";break;
            case 5: Cap05name = "5";break;
            case 6: Cap06name = "6";break;
            case 7: Cap07name = "7";break;
            case 8: Cap08name = "8";break;
            case 9: Cap09name = "9";break;
            case 10: Cap10name = "10";break;
            case 11: Cap11name = "11";break;
            case 12: Cap12name = "12";break;
            case 13: Cap13name = "13";break;
            case 14: Cap14name = "14";break;
            case 15: Cap15name = "15";break;
            case 16: Cap16name = "16";break;
            case 17: Cap17name = "17";break;
            default: break;
        }
        capAvaliable[getPendingCap()] = 1;
        addLog(0);
    }
}
void handlePut()
{
    if(pending){esp8266_server.send(200, "text/html",sendPending());}
    else
    {
        esp8266_server.send(200, "text/html",sendPut());
        pendingCap = esp8266_server.arg("Cap");
        pending = 1;
    }
}
void handleNote()
{
    if(pending){esp8266_server.send(200, "text/html",sendPending());}
    else
    {
        esp8266_server.send(200, "text/html",sendNote());
    }
}
void handleInfoInsert()
{
    if(pendingCap == String("25")){esp8266_server.send(404, "text/plain", "404: Not found");}
    else
    {
        esp8266_server.send(200, "text/html",sendInfoInsert());
        switch(getPendingCap())
        {
            case 0: Cap00name = esp8266_server.arg("name");break;
            case 1: Cap01name = esp8266_server.arg("name");break;
            case 2: Cap02name = esp8266_server.arg("name");break;
            case 3: Cap03name = esp8266_server.arg("name");break;
            case 4: Cap04name = esp8266_server.arg("name");break;
            case 5: Cap05name = esp8266_server.arg("name");break;
            case 6: Cap06name = esp8266_server.arg("name");break;
            case 7: Cap07name = esp8266_server.arg("name");break;
            case 8: Cap08name = esp8266_server.arg("name");break;
            case 9: Cap09name = esp8266_server.arg("name");break;
            case 10: Cap10name = esp8266_server.arg("name");break;
            case 11: Cap11name = esp8266_server.arg("name");break;
            case 12: Cap12name = esp8266_server.arg("name");break;
            case 13: Cap13name = esp8266_server.arg("name");break;
            case 14: Cap14name = esp8266_server.arg("name");break;
            case 15: Cap15name = esp8266_server.arg("name");break;
            case 16: Cap16name = esp8266_server.arg("name");break;
            case 17: Cap17name = esp8266_server.arg("name");break;
            default: break;
        }
        capAvaliable[getPendingCap()] = 0;
        if(String("1") == esp8266_server.arg("ifNote"))
        {
            userInputNote = esp8266_server.arg("note");
            capNote[getPendingCap()] = 1;
        }
        userInputTime = esp8266_server.arg("alerttime");
        addLog(1);
    }
}
void handleTimeSet()
{
    if(pending){esp8266_server.send(200, "text/html",sendPending());}
    else
    {
        esp8266_server.send(200, "text/html",sendTimeSet());
    }
}
void handleSetDone()
{
    esp8266_server.send(200, "text/html",sendSetDone());
    String fixedYY =  esp8266_server.arg("yy");
    String fixedMM =  esp8266_server.arg("mm");
    String fixedDD =  esp8266_server.arg("dd");
    String fixedHH =  esp8266_server.arg("hh");
    String fixedMin =  esp8266_server.arg("min");
    webTime[0] = fixedYY.toInt();
    webTime[1] = fixedMM.toInt();
    webTime[2] = fixedDD.toInt();
    webTime[3] = fixedHH.toInt();
    webTime[4] = fixedMin.toInt();
}
void handleWLANconnect()
{
    if(1 == internetConnected){esp8266_server.send(200, "text/html",sendConnected());}
    else
    {
        esp8266_server.send(200, "text/html",sendWLANconnect());
    }
}
void handleConnected()
{
    if(internetConnected){esp8266_server.send(200, "text/html", sendConnected());}
    else{esp8266_server.send(404, "text/plain", "404: Not found");} 
}
void handleTrying()
{
    esp8266_server.send(200, "text/html", sendTrying());
    String fixedSSID =  esp8266_server.arg("ssid");
    String fixedPW =  esp8266_server.arg("password"); 
    char cFixedSSID[fixedSSID.length() + 1];
    fixedSSID.toCharArray(cFixedSSID, fixedSSID.length() + 1);
    char cFixedPW[fixedPW.length() + 1];
    fixedPW.toCharArray(cFixedPW, fixedPW.length() + 1);
    wifiMulti.addAP(cFixedSSID,cFixedPW); 
    int wifiTimeOutCounter=0;
    internetConnected = 1;
    if(0 == offlineMode){offlineMode = 1;}
    while (wifiMulti.run() != WL_CONNECTED) 
    {
        for(int i=0;100>i;i++){PWM(LED_BUILTIN,100,i,5,ON);}
        delay(10);
        for(int i=100;0<i;i--){PWM(LED_BUILTIN,100,i,5,OFF);}
        delay(800);
        wifiTimeOutCounter++;
        if(5<=wifiTimeOutCounter){internetConnected=0;break;}
    }
}
void handleConfirm()
{
    esp8266_server.send(200, "text/html",sendConfirm());
    if(1 == internetConnected){internetConfirmation = 1;}
}
void handleOffline()
{
    if(pending){esp8266_server.send(200, "text/html",sendPending());}
    else
    {
        esp8266_server.send(200, "text/html",sendOffline());
    }
    offlineMode = 1;
}
void handleNotFound()
{  esp8266_server.send(404, "text/plain", "404: Not found"); delay(500);  }
/* <!-- END --> */


void HTMLsetup(bool ifSerial = 0)
{
    WiFi.softAP(ssid, password,1,0,4);//channel=1,hidden=0,MaxConnections=1
    if(ifSerial)
    {
        Serial.print("Access Point: ");
        Serial.println(ssid);
        Serial.print("IP address: ");
        Serial.println(WiFi.softAPIP());
        Serial.println("Connecting ...");  
    }
    /*esp8266_server.begin();                  
    esp8266_server.on("/",handleRoot);
    esp8266_server.on("/Dev",handleDev);
    esp8266_server.on("/Stat",handleStat);
        esp8266_server.on("/Stat/info",handleInfo);
            esp8266_server.on("/Stat/info/devinfo",handleDevInfo);
        esp8266_server.on("/Stat/log",handleLog);
        esp8266_server.on("/Stat/manage",handleManage);
            esp8266_server.on("/Stat/manage/Get",handleGet);
            esp8266_server.on("/Stat/manage/Put",handlePut);
                esp8266_server.on("/Stat/manage/Put/infoInsert",handleInfoInsert);
        esp8266_server.on("/Stat/Note",handleNote);
    esp8266_server.on("/TimeSet",handleTimeSet);
        esp8266_server.on("/TimeSet/SetDone",handleSetDone);
    esp8266_server.on("/WLANconnect",handleWLANconnect);
        esp8266_server.on("/WLANconnect/connected",handleConnected);
        esp8266_server.on("/WLANconnect/Trying",handleTrying);
            esp8266_server.on("/WLANconnect/connected/confirm",handleConfirm);
        esp8266_server.on("/WLANconnect/offline",handleOffline);*/
    esp8266_server.begin();                  
    esp8266_server.on("/",handleRoot);
    esp8266_server.on("/Dev",handleDev);
    esp8266_server.on("/Stat",handleStat);
        esp8266_server.on("/info",handleInfo);
            esp8266_server.on("/devinfo",handleDevInfo);
        esp8266_server.on("/log",handleLog);
        esp8266_server.on("/manage",handleManage);
            esp8266_server.on("/Get",handleGet);
            esp8266_server.on("/Put",handlePut);
                esp8266_server.on("/infoInsert",handleInfoInsert);
        esp8266_server.on("/Note",handleNote);
    esp8266_server.on("/TimeSet",handleTimeSet);
        esp8266_server.on("/SetDone",handleSetDone);
    esp8266_server.on("/WLANconnect",handleWLANconnect);
        esp8266_server.on("/connected",handleConnected);
        esp8266_server.on("/Trying",handleTrying);
            esp8266_server.on("/confirm",handleConfirm);
        esp8266_server.on("/offline",handleOffline);
    //esp8266_server.on("/",handle);
    esp8266_server.onNotFound(handleNotFound);

    int i=17;
    while(0 <= i)
    {
        capAvaliable[i]=1;
        capNote[i]=0;
        i--;
    }
    pending = 0;
}
void HTTPloop(bool ifSerial = 1)
{
    if(ifSerial)
    {
        Serial.println("Looping");
    }
    if(debugMode)
    {
        Serial.print("Var16:");
        Serial.println(capAvaliable[16]);
    }
    esp8266_server.handleClient();
}
