#include <WiFi.h>
#include <WiFiClient.h>
#include <WiFiAP.h>
#include <WebServer.h>
#include <ESPmDNS.h>

#define yellow_LED 11
#define green_LED 8
#define red_LED 16

const char* ssid = "Renato";
const char* password = "0987654321";

WebServer server(80);

void setup() {
  pinMode(yellow_LED, OUTPUT);
  pinMode(green_LED, OUTPUT);
  pinMode(red_LED, OUTPUT);

  Serial.begin(115200);

  WiFi.softAP(ssid, password);
  IPAddress myIP = WiFi.softAPIP();

  Serial.print("SSID: ");
  Serial.println(ssid);
  Serial.print("AP IP Address: ");
  Serial.println(myIP);
  server.begin();
  Serial.println("Servidor iniciado!");

  if (MDNS.begin("esp32")) {
    Serial.println("MDNS responder started");
  }

  server.on("/", handleRoot);
  server.on("/brightYellow", handleYellowOn);
  server.on("/brightGreen", handleGreenOn);
  server.on("/brightRed", handleRedOn);
  server.on("/off", handleOff);
  server.onNotFound(handleNotFound);
  server.begin();
  
  Serial.println("HTTP server started");
}

void handleRoot() {
  String html = "<!DOCTYPE html><html><body>    <div id='finish'>       <div class='win-screen'>            <div class='victory'>                Resultado            </div>";
  html += "<div id='result'>            </div>            <div class='restart-button'>                <button onclick='restartGame()'>Reiniciar</button>            </div>        </div>    </div>";
  html += "<div class='full-table'>        <div class='table-row'>            <div id='0' class='table-frame' onclick='addSymbol(0)'></div>";
  html += "<div id='1' class='table-frame' onclick='addSymbol(1)'></div>            <div id='2' class='table-frame' onclick='addSymbol(2)'></div>        </div>        <div class='table-row'>";
  html += "<div id='3' class='table-frame' onclick='addSymbol(3)'></div>            <div id='4' class='table-frame' onclick='addSymbol(4)'></div>            <div id='5' class='table-frame'";
  html += "onclick='addSymbol(5)'></div>        </div>        <div class='table-row'>            <div id='6' class='table-frame' onclick='addSymbol(6)'></div>            <div id='7'";
  html += "class='table-frame' onclick='addSymbol(7)'></div>            <div id='8' class='table-frame' onclick='addSymbol(8)'></div>        </div>    </div>    <style>        * {"   ;         
  html += "margin: 0;            padding: 0;            font-family: 'Poppins', sans-serif;        }        body {";
  html += "display: flex;            background-color: #8D9EFF;            align-items: center;            justify-content: center;            width: 100vw;            height: 100vh; "           ;
  html += "overflow: hidden;        }        .full-table {            display: flex;            flex-direction: column;            background-color: #8D9EFF;            gap: 10px;    "        ;
  html += "width: 40%;            height: 80%;        }        .table-row {            display: flex;            flex-direction: row;            gap: 10px;            height: 33.3%;  "         ; 
  html += "width: 100%;        }        .table-frame {            display: flex;            border-radius: 15px;            background-color: #FFFFFF;            align-items: center; "          ; 
  html += "justify-content: center;            user-select: none;            width: 33.3%;            height: 100%;            font-size: 100px;            color: #8D9EFF;        }  "      ;
  html += ".table-frame:hover {            background-color: #F0F0F0;        }        #finish {            display: none;            align-items: center;            justify-content: center; "           ;
  html += "width: 100%;            height: 100%;            background-color: #0F0F0F40;            position: absolute;        }        .win-screen {            display: flex;        "    ;
  html += "align-items: center;            justify-content: center;            flex-direction: column;            ";
  html += "background-color: #FFFFFF;            border-radius: 15px;            width: 35%;            height: 40%;        }        #result {            display: flex;            ";
  html += "justify-content: center;            align-items: center;            height: 33.3%;            font-size: 75px;        }        .victory {            display: flex;       " ;    
  html += "justify-content: center;            align-items: center;            height: 33.3%;            font-size: 75px;        }        .restart-button {            display: flex;    ";        
  html += "justify-content: center;            align-items: center;            height: 33.3%;            width: 100%;        }        .restart-button button {            border-style: none; ";           
  html += "border-radius: 15px;            background-color: #8D9EFF;            width: 50%;            height: 50%;            color: #FFFFFF;            font-size: 30px;        }        ";
  html += ".restart-button button:hover {            cursor: pointer;        }    </style>    <script>        var order = true;        var selected = [];        var winCombination = [    "  ;      
  html += "[0, 1, 2],            [3, 4, 5],            [6, 7, 8],            [0, 3, 6],            [1, 4, 7],            [2, 5, 8],            [0, 4, 8],            [2, 4, 6]        ];  "    ;  
  html += "var win = false;        function addSymbol(index) {            if (!win) {                var canSelect = true;                ";
  html += "for (var i = 0; i < selected.length; i++) {                    if (selected[i] == index) {                        canSelect = false;                        break;"               ;
  html += "}                }                if (canSelect) {                    if (order) {                        document.getElementById(index).innerHTML = 'X';   "                     ;
  html += "document.getElementById(index).value = 'X';                        selected.push(index);                        order = false;                    }                    else {"       ;              
  html += "document.getElementById(index).innerHTML = 'O';                        document.getElementById(index).value = 'O';                        selected.push(index);";
  html += "order = true;                    }                }                verifyWin();            }        }        function verifyWin() {            for (var i = 0; i < winCombination.length; i++)";
  html += "{                one = document.getElementById(winCombination[i][0]).value;                two = document.getElementById(winCombination[i][1]).value;";
  html += "three = document.getElementById(winCombination[i][2]).value;                console.log(one);                if (one == 'X' && two == 'X' && three == 'X') {"     ;           
  html += " newWindow = window.open('http://192.168.4.1/brightGreen'); setTimeout(function(){ newWindow.close();}, 10); win = true;                    winScreen('X');                }                else if (one == 'O'";
  html += "&& two == 'O' && three == 'O') {  newWindow = window.open('http://192.168.4.1/brightYellow'); setTimeout(function(){ newWindow.close();}, 10);     win = true;                    winScreen('O');                }";
  html += "else if (selected.length == 9) {  newWindow = window.open('http://192.168.4.1/brightRed'); setTimeout(function(){ newWindow.close();}, 10); win = true; winScreen('Empate');}       }        }        function winScreen(symbol) {";          
  html += "document.getElementById('finish').style.display = 'flex';            document.getElementById('result').innerHTML = symbol;            if (symbol == 'X') {"      ;
  html += "document.getElementById('result').style.color = 'green';            }            else if (symbol == 'O'){                document.getElementById('result').style.color = 'yellow';  "   ;       
  html += "} else { document.getElementById('result').style.color = 'red';   }       }        function restartGame() {            document.location.href = 'http://192.168.4.1/off';        }    </script></body></html>";

  server.send(200, "text/html", html);
}

void handleGreenOn() {
  digitalWrite(green_LED, 1);

  handleRoot();
}

void handleYellowOn() {
  digitalWrite(yellow_LED, 1);

  handleRoot();
}

void handleRedOn() {
  digitalWrite(red_LED, 1);

  handleRoot();
}

void handleOff() {
  digitalWrite(green_LED, 0);
  digitalWrite(yellow_LED, 0);
  digitalWrite(red_LED, 0);
  handleRoot();
}

void handleNotFound() {
  digitalWrite(red_LED, 1);
  digitalWrite(yellow_LED, 1);
  digitalWrite(green_LED, 1);
  String message = "File Not Found\n\n";
  message += "URI: ";
  message += server.uri();
  message += "\nMethod: ";
  message += (server.method() == HTTP_GET) ? "GET" : "POST";
  message += "\nArguments: ";
  message += server.args();
  message += "\n";
  for (uint8_t i = 0; i < server.args(); i++) {
    message = +" " + server.argName(i) + ": " + server.arg(i) + "\n";
  }
  server.send(404, "text/plain", message);
  digitalWrite(yellow_LED, 0);
  digitalWrite(red_LED, 0);
  digitalWrite(green_LED, 0);
}

void loop(void) {
  server.handleClient();
  delay(2);
}