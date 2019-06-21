
var ws;
let mountains = [
  { name: "Monte Falco", height: 1658, place: "Parco Foreste Casentinesi" },
  { name: "Monte Falterona", height: 1654, place: "Parco Foreste Casentinesi" },
  { name: "Poggio Scali", height: 1520, place: "Parco Foreste Casentinesi" },
  { name: "Pratomagno", height: 1592, place: "Parco Foreste Casentinesi" },
  { name: "Monte Amiata", height: 1738, place: "Siena" }];


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

      switch (obj.type){
        case 0:
          document.getElementById("text2").value = obj.value;
        break;
        case 1:
          document.getElementById("text3").value = obj.value;
        break;
        case 2:
          document.getElementById("text4").value = obj.value;
        break;
        case 3:
          updateTable();
        break;
        default:
      }
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



function generateTableHead(table, data) {
  let thead = table.createTHead();
  let row = thead.insertRow();
  for (let key of data) {
    let th = document.createElement("th");
    let text = document.createTextNode(key);
    th.appendChild(text);
    row.appendChild(th);
  }
}

function generateTable(table, data) {
  for (let element of data) {
    let row = table.insertRow();
    for (key in element) {
      let cell = row.insertCell();
      let text = document.createTextNode(element[key]);
      cell.appendChild(text);
    }
  }
}

function updateTable(){
  let table = document.querySelector("table");
  let data = Object.keys(mountains[0]);
  generateTable(table, mountains);
  generateTableHead(table, data);  
}
