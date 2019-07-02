
function jsonRX(json_data){

	var obj = JSON.parse(json_data);


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
		  updateTable("table1", obj.value);

		break;
		default:
	}
}


function jsonTX(json_data){
	var obj = json_data; // = JSON.stringify(json_data);
	output("request: " + obj);
	ws.send(obj);
}



function dispFile(contents) {
  output(contents);
}
function clickElem(elem) {
  // Thx user1601638 on Stack Overflow (6/6/2018 - https://stackoverflow.com/questions/13405129/javascript-create-and-save-file )
  var eventMouse = document.createEvent("MouseEvents")
  eventMouse.initMouseEvent("click", true, false, window, 0, 0, 0, 0, 0, false, false, false, false, 0, null)
  elem.dispatchEvent(eventMouse)
}
function openFile(func) {
  readFile = function(e) {
    var file = e.target.files[0];
    if (!file) {
      return;
    }
    var reader = new FileReader();
    reader.onload = function(e) {
      var contents = e.target.result;
      fileInput.func(contents)
      document.body.removeChild(fileInput)
    }
    reader.readAsText(file)
  }
  fileInput = document.createElement("input")
  fileInput.type='file'
  fileInput.style.display='none'
  fileInput.onchange=readFile
  fileInput.func=func
  document.body.appendChild(fileInput)
  clickElem(fileInput)
}