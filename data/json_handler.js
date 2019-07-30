
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

	output("< " + json_data);

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
		  //document.getElementById("text4").value = obj.value;
		break;
		case 3:
			updateTable("wifi-table", obj.value);

		break;
		default:
	}
}