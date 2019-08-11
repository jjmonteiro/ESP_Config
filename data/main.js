
var ws;
var debug = true;
var myIP = "%IPADDR%";

var CHECK_CONNECTION_INTERVAL = 5000;
var UPDATE_VALUES_INTERVAL = 2000;


function init() {
  var host;

  setInterval(checkConnection, CHECK_CONNECTION_INTERVAL);

  if (isValidIP(myIP)){
    host = "ws://" + myIP + "/ws";
  }else{
    host = "ws://localhost:81";
  }

  document.getElementById("val-host").innerHTML = host;
  ws = new WebSocket(host);


  ws.onmessage = function(e) {
    
    // e.data contains received string.
    if (e.data){
      output("reply: " + e.data);
      jsonRX(e.data);
    }
  };

  ws.onopen = function(e) {
    updateStatus.run = setInterval(updateStatus, UPDATE_VALUES_INTERVAL);
    //checkConnection();
    //document.getElementById("button1").innerHTML = "Close";
  };
  ws.onclose = function(e) {
    clearInterval(updateStatus.run);
    //checkConnection();
    //document.getElementById("button1").innerHTML = "Open";
  };
}

function isValidIP(ipaddress) {  
  if (/^(25[0-5]|2[0-4][0-9]|[01]?[0-9][0-9]?)\.(25[0-5]|2[0-4][0-9]|[01]?[0-9][0-9]?)\.(25[0-5]|2[0-4][0-9]|[01]?[0-9][0-9]?)\.(25[0-5]|2[0-4][0-9]|[01]?[0-9][0-9]?)$/.test(ipaddress)) {  
    return true; 
  }   
  return false; 
}  


function updateStatus(){
  jsonTX(JSON.stringify({"type":2}));
}

function checkConnection(){

  var status = document.getElementById("val-status");
  var reply;


  switch (ws.readyState){
    case 0:
      reply = "connecting.."
    break;
    case 1:
      reply = "connected."
      
      //updateFields();
    break;
    case 2:
      reply = "disconnecting.."
    break;
    case 3:
      reply = "disconnected."
      ws.close();
      init();
    break;
    default:
      reply = "unknown status."
  }
  status.innerHTML = reply;
  //output(reply);
}

function onSend() {
  var input = document.getElementById("ter-input");
  
    if(ws.readyState!=1){
      output("> not connected!");
    }else{
      jsonTX(input.value);
    }
  
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
    if (e.which === 13) {
      onSend();
    }
    if (e.which === 27) {
      onClear();
    }
}

function toggleMenu() {
  var x = document.getElementById("navDemo");
  if (x.className.indexOf("w3-show") == -1) {
    x.className += " w3-show";//open
  } else { //close
    x.className = x.className.replace(" w3-show", "");
  }
}


function closeMenu() {
  closeSubMenu();
  var x = document.getElementById("navDemo");
  if (x.className.indexOf("w3-show") != -1) {
    x.className = x.className.replace(" w3-show", "");
  }
}

function toggleSubMenu() {
  var x = document.getElementById("demoAcc");
  if (x.className.indexOf("w3-show") == -1) {
    x.className += " w3-show";
    x.previousElementSibling.className += " w3-light-grey";
  } else { 
    x.className = x.className.replace(" w3-show", "");
    x.previousElementSibling.className = 
    x.previousElementSibling.className.replace(" w3-light-grey", "");
  }
}

function closeSubMenu() {
  var x = document.getElementById("demoAcc");
  if (x.className.indexOf("w3-show") != -1) {
    x.className = x.className.replace(" w3-show", "");
    x.previousElementSibling.className = 
    x.previousElementSibling.className.replace(" w3-light-grey", "");
  }
}

function showOnly(id) {
  var x = document.getElementsByClassName("page");
  for (i = 0; i < x.length; i++) {
      document.getElementById(x[i].id).style.display = 'none';
  }
  document.getElementById(id).style.display = 'block';
}

function powerMenu(){
  
  alert("Sure to power off?");
  
  var x = document.getElementById("ic-wifi");
  
  //test for icon update
  // if (x.hasAttribute("data-icon")) {
  //   x.setAttribute("data-icon", "ic:round-wifi");
  // }
  
}

function updateValues(dataValues){
  myObj = dataValues[0];
  for (key in myObj) {
    var value = myObj[key]+"%";

    var elem = document.getElementById("bar-"+key);
    elem.style.width = value;

    var elem = document.getElementById("val-"+key);
    elem.innerHTML = value;
  }
}


function updateTable(tableId, jsonData){

  var tableHTML = "<thead><tr class='w3-black'>";
  for (var headers in jsonData[0]) {
    tableHTML += "<th>" + headers + "</th>";
  }
  tableHTML += "</tr></thead>";
  
  for (var eachItem in jsonData) {
    tableHTML += "<tr>";
    var dataObj = jsonData[eachItem];
    for (var eachValue in dataObj){
      tableHTML += "<td>" + dataObj[eachValue] + "</td>";
    }
    tableHTML += "</tr>";
  }
  
  document.getElementById(tableId).innerHTML = tableHTML;
}

function IsJsonString(str) {
    try {
        JSON.parse(str);
    } catch (e) {
        return false;
    }
    return true;
}

function jsonTX(json_data){

  if (!json_data){return;}

  output("> " + json_data);

  if (!IsJsonString(json_data)){
    json_data = JSON.stringify({"type":0,"value":json_data})
  }

  ws.send(json_data);
}


function jsonRX(json_data){

  if (!IsJsonString(json_data)){return;}

  var obj = JSON.parse(json_data);

  switch (obj.type){
    case 0:
      //document.getElementById("text2").value = obj.value;
    break;
    case 1:
      //document.getElementById("text3").value = obj.value;
    break;
    case 2:
      updateValues(obj.value);
    break;
    case 3:
      updateTable("wifi-table", obj.value);

    break;
    default:
  }
}

