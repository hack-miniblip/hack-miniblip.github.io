function detect_board() {


} 


function upload_firmware() {


} 


function init_console(div) {


} 


function get_list_firmwares_remote() {


}

function get_list_firmwares_local() {
	var fs = require("fs");
	console.log(process.cwd());

	fs.readFile("firmwares.json", "utf8", function(error, data) {
		console.log(data);
		var obj = $.parseJSON( data );

		for (var i = 0; i < obj.length; i++) {
			console.log(obj[i].name);
			$("#firmwares").append('<div class="item"><div class="name">' + obj[i].name +'</div><div class="author">'+obj[i].author+'</div></div>');
		}
		//console.log(obj);
	});	
}


//check md5
function download_firmware() {

}
