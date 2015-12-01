function detect_board() {


} 

function upload_firmware(path_in, path_out) {
	var cmd_dd = "sudo dd if="+path_in+" of="+path_out+" bs=512 seek=4 conv=notrunc";

	console.log(cmd_dd);


	var execFile = require 
	    ('child_process').execFile, child;

	 child = execFile(cmd_dd,
	       function(error,stdout,stderr) { 
	    if (error) {
	      console.log(error.stack); 
	      console.log('Error code: '+ error.code); 
	      console.log('Signal received: '+ 
		     error.signal);
	      } 
	    console.log('Child Process stdout: '+ stdout);
	    console.log('Child Process stderr: '+ stderr);
	  }); 
	  child.on('exit', function (code) { 
	    console.log('Child process exited '+
		'with exit code '+ code);
	  });
} 


function init_console(div) {


} 


function get_list_firmwares_remote() {


}

function get_local_firmware_path(firmware_name) {
	var base = process.cwd() + "/firmwares-prueba/";
	
	var path = base + "firmware_name";
	console.log(path);

	return path;
}

function get_remote_firmware_url() {


}

function get_list_firmwares_local() {
	var fs = require("fs");
	console.log(process.cwd());

	fs.readFile("firmwares.json", "utf8", function(error, data) {
		console.log(data);
		var obj = $.parseJSON( data );

		$.each(obj, function(i, value) {
			console.log(obj[i].name);
			$("#firmware-list").append('<div class="item" id = '+obj[i].id +'><div class="name">' + obj[i].name +'</div><div class="author">'+obj[i].author+'</div></div>');
			$("#firmware-list #" + obj[i].id).click(function() {
				upload_firmware(get_local_firmware_path(obj[i].id), "/dev/sdb");
			});
		});
		//console.log(obj);
	});	
}


//check md5
function download_firmware() {

}




function bind_buttons() {
	$("#toolbar #list").click(function() {
		hide_all_sections();
		$("#main #firmware-list").show();
	});

	$("#toolbar #console").click(function() {
		hide_all_sections();
		$("#main #console").show();
	});

	$("#toolbar #code").click(function() {
		hide_all_sections();
		$("#main #editor-container").show();
	});
}


function hide_all_sections() {
	$("#main #editor-container").hide();

} 

function show_section() {
	

}
