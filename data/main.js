
var ws;
var debug = true;

function init() {
  var timer1;

  ws = new WebSocket("ws://localhost:81");
  //ws = new WebSocket("ws://%IPADDR%/ws");
  
  ws.onmessage = function(e) {
    
    // e.data contains received string.
    if (e.data){
      output("reply: " + e.data);
      jsonRX(e.data);
    }
  };

  ws.onopen = function(e) {
    timer1 = setInterval(checkConnection, 5000);
    checkConnection();
    //document.getElementById("button1").innerHTML = "Close";
  };
  ws.onclose = function(e) {
    //clearInterval(timer1);
    checkConnection();
    //document.getElementById("button1").innerHTML = "Open";
  };
}



function updateFields(){
  jsonTX(JSON.stringify({"type":0,"value":"ping"}));
}

function checkConnection(){

  var status = document.getElementById("ter-main");
  var reply;


  switch (ws.readyState){
    case 0:
      reply = "Connecting.."
    break;
    case 1:
      reply = "Connected."
      //updateFields();
    break;
    case 2:
      reply = "Disconnecting.."
    break;
    case 3:
      reply = "Disconnected."
        document.getElementById("ter-main");
        ws.close();
        init();
    break;
    default:
      reply = "Unknown Status."
  }
  //output(reply);
}

function onSend() {
  var input = document.getElementById("ter-input");
  jsonTX(input.value);
  input.value = "";
}


function onClear() {
  var log = document.getElementById("ter-main");
  log.innerHTML = "";
}

function output(str) {
  var log = document.getElementById("ter-main");
  //var escaped = str.replace(/&/, "&amp;").replace(/</, "&lt;").
  //replace(/>/, "&gt;").replace(/"/, "&quot;"); // "
  log.innerHTML += str + '\n';
  log.scrollTop = log.scrollHeight;
}


function toggleGrey(elementid){
  var status = document.getElementById(elementid);
  status.disabled = !status.disabled;
}

function runScript(e) {
    if (e.which == 13) {
        onSend();
    }
}