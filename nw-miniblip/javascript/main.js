// TODO 
// GET REMOTE JSON
// DOWNLOAD FILE ON ITEM CLICK 
// CHECK BOARD STATUS 
// UPLOAD FIRMWARE 
//
var fs = require("fs");
var http = require('http');


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

	var url = "https://raw.githubusercontent.com/hack-miniblip/apps/master/firmware_list.json"; 

	$.get(url, function(data) {
	  var obj = $.parseJSON(data);
	  $.each(obj, function(i, value) {
		add_item_to_firmware_list(obj[i], true);
	  });

	});
}

function get_local_firmware_path(firmware_name) {
	var base = process.cwd() + "/firmwares-prueba/";
	
	var path = base + "firmware_name";
	console.log(path);

	return path;
}

function get_remote_firmware_url(name) {
	return "https://github.com/hack-miniblip/apps/raw/master/"+name+"/firmware.bin";
}

function add_item_to_firmware_list(obj, isRemote) {
	console.log("added " + obj.name);	
	var file_url = "";	
	if (isRemote) {
		file_url = get_remote_firmware_url(obj.name);
console.log(file_url);
	} else { 
		file_url = get_local_firmware_path(obj.name);
	}

	$("#firmware-list").append('<div class="item" id = '+obj.id +'><div class="name">' + obj.name +'</div><div class="author">'+obj.author+'</div></div>');
			$("#firmware-list #" + obj.id).click(function() {

				if (isRemote) {
					download_firmware(file_url, function() {
						//upload_firmware(file_url, "/dev/sdb");
					});
				} else {
					upload_firmware(file_url, "/dev/sdb");	
				}

			});
}

function get_list_firmwares_local() {
	console.log(process.cwd());

	fs.readFile("firmwares.json", "utf8", function(error, data) {
		console.log(data);
		var obj = $.parseJSON( data );

		$.each(obj, function(i, value) {
			add_item_to_firmware_list(obj[i]);
		});
		//console.log(obj);
	});   
} 


//TODO check md5
function download_firmware(name, url, callback) {
	if (!fs.existsSync("./tmp")){
    		fs.mkdirSync("./tmp");
	}

	var path = process.cwd() + "/" + name;

	var file = fs.createWriteStream(path);

	var request = http.get(url, function (response) {
	    response.pipe(file);
	    callback();
	});
}


function show_section_firmware_list() {
	$("#main #firmware-list").show();
}

function show_section_code() {
	$("#main #editor-container").show();
}

function bind_buttons() {
	$("#toolbar #list").click(function() {
		hide_all_sections();
		show_section_firmware_list();
	});

	$("#toolbar #console").click(function() {
		hide_all_sections();
		$("#main #console").show();
	});

	$("#toolbar #code").click(function() {
		hide_all_sections();
		show_section_code();
	});
}


function hide_all_sections() {
	$("#main #editor-container").hide();

} 

function show_section() {
	

}

//interval of given delat, will execute callback with [true] or [false] as param
function check_serial_connected(delay, callback) {
	setInterval(function(){
	var cmd = "ls /dev/ttyACM*";
	try {
		var res = require('child_process').execSync(cmd, {
			stdio: "pipe",
			stderr: "pipe"
		}).toString();

	if (!res || res.length === 0 || res === undefined) res = false;
	else res = true;
	}
	catch (err){
		res = false;
	}
	callback(res);	
	},delay);
}
