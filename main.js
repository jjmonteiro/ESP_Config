
var ws;

function init() {
  var timer1;
  var timer2;

  // Connect to Web Socket
  ws = new WebSocket("ws://localhost:81/");
  
  ws.onmessage = function(e) {

    // e.data contains received string.
    if (e.data != '0'){
      output("reply: " + e.data);
      var obj = JSON.parse(e.data);

      document.getElementById("text2").value = obj.type;
      document.getElementById("text3").value = obj.value;
    }
  };

  ws.onopen = function(e) {
    timer1 = setInterval(checkConnection, 5000);
    timer2 = setInterval(updateFields, 5000);
    checkConnection();
    document.getElementById("button1").innerHTML = "Close";
  };
  ws.onclose = function(e) {
    //clearInterval(timer1);
    clearInterval(timer2);
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
  ws.send("s1");
  output("auto request: s1");
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
  var input = document.getElementById("text5");

  ws.send(input.value);
  output("request: " + input.value);
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
  var log = document.getElementById("log");
  var escaped = str.replace(/&/, "&amp;").replace(/</, "&lt;").
    replace(/>/, "&gt;").replace(/"/, "&quot;"); // "
  log.innerHTML = escaped + "<br>" + log.innerHTML;
}
