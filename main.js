
var ws;
var speed = 0;

function init() {
  setInterval(updateSpeed, 1000);
  // Connect to Web Socket
  ws = new WebSocket("ws://localhost:81/");
  
  ws.onmessage = function(e) {
    speed++;

    sleep(2);//to limit cpu stress

    ws.send('0');
    // e.data contains received string.
    if (e.data != '0'){
      output("reply: " + e.data);
      var obj = JSON.parse(e.data);

      document.getElementById("sensor_1").value = obj.type;
      document.getElementById("sensor_2").value = obj.value;
    }


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

function updateSpeed(){
  var stt = document.getElementById("status");
  var spd = document.getElementById("speed");
  spd.value = speed;
  if (speed){
    stt.value = "Connected.";
  }else{
    stt.value = "Disconnected.";
  }
  speed = 0;
}

function onSubmit() {
  var input = document.getElementById("input");
  // You can send message to the Web Socket using ws.send.
  ws.send(input.value);
  output("request: " + input.value);
  input.value = "";
  input.focus();
}

function onCloseClick() {
  ws.close();
}

function output(str) {
  var log = document.getElementById("log");
  var escaped = str.replace(/&/, "&amp;").replace(/</, "&lt;").
    replace(/>/, "&gt;").replace(/"/, "&quot;"); // "
  log.innerHTML = escaped + "<br>" + log.innerHTML;
}
