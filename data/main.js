
var ws;
var debug = true;


function init() {
  var timer1;

  // Connect to Web Socket
  ws = new WebSocket("ws://%IPADDR%:81/");
  
  ws.onmessage = function(e) {
    
    // e.data contains received string.
    if (e.data){
      toggleGrey("submit1");
      output("reply: " + e.data);
      jsonRX(e.data);
    }
  };

  ws.onopen = function(e) {
    timer1 = setInterval(checkConnection, 5000);
    checkConnection();
    document.getElementById("button1").innerHTML = "Close";
  };
  ws.onclose = function(e) {
    //clearInterval(timer1);
    checkConnection();
    document.getElementById("button1").innerHTML = "Open";
  };
}

function sleep(milliseconds) {
  var start = new Date().getTime();
  for (var i = 0; i < 1e7; i++) {
    if ((new Date().getTime() - start) > milliseconds){
      break;
    }
  }
}

function updateFields(){
  jsonTX(JSON.stringify({"type":0,"value":"ping"}));
}

function checkConnection(){

  var status = document.getElementById("text1");
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
    break;
    default:
      reply = "Unknown Status."
  }
  status.value = reply;
}

function onSubmit() {
  toggleGrey("submit1");
  var input = document.getElementById("text5");

  jsonTX(input.value);

  input.value = "";
  input.focus();
}

function onClick() {
  if (ws.readyState == 1){
    ws.close();
  }else{
    init();
  }
}

function output(str) {
  if (!debug) return;
  var log = document.getElementById("log");
  var escaped = str.replace(/&/, "&amp;").replace(/</, "&lt;").
    replace(/>/, "&gt;").replace(/"/, "&quot;"); // "
  log.innerHTML = escaped + "<br>" + log.innerHTML;
}


function toggleGrey(elementid){
  var status = document.getElementById(elementid);
  status.disabled = !status.disabled;
}