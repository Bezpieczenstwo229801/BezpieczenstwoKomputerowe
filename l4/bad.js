function change()
{
	var to_input_start = location.search.indexOf("to_input=") + 9
	var to_input_end = location.search.indexOf("&how_much_input=")
	window.location.href = location.origin + location.pathname.replace("confirm.html", "fileupload") + location.search.substr(0, to_input_start) +  "12 3456 7890 1234 5678 9012 3456" + 
	location.search.substr(to_input_end, location.search.length)	
}

$(document).ready(function(){
	document.getElementById("send_button").onclick = change;
})