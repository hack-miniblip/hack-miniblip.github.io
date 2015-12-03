// TODO 
// OK - GET REMOTE JSON
// OK - DOWNLOAD FILE ON ITEM CLICK 
// CHECK BOARD STATUS 
// UPLOAD FIRMWARE 
//
var fs = require("fs");
var https = require('https');
var md5 = require('md5');
var httpreq = require('httpreq');
var sudo = require('sudo-prompt');



function detect_board() {


} 

function upload_firmware(path_in) {
	var path_out = "/dev/sdb";
	var cmd_dd = "dd if="+path_in+" of="+path_out+" bs=512 seek=4 conv=notrunc";

	console.log(cmd_dd);


	var options = {
	  name: 'MiniBlip Studio',
	  onChildProcess: function(childProcess) {} // (optional)
	};
	sudo.exec(cmd_dd, options, function(error, stdout, stderr) {
		console.log("error " + error);
		console.log("stdout " + stdout);
		console.log("stderr " + stderr);
	})

	/*
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
	*/
} 


function init_console(div) {


} 


function get_list_firmwares_remote() {

	var url = "https://raw.githubusercontent.com/hack-miniblip/apps/master/firmware_list.json"; 

	$.get(url, function(data) {
	  var obj = $.parseJSON(data);

	  
	  $.each(obj, function(i, value) {
		add_item_to_firmware_list(value, true);
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
	} else { 
		file_url = get_local_firmware_path(obj.name);
	}


	$item = $('<div class="item" id = '+obj.id +'><div class="name">' + obj.name +'</div><div class="author">'+obj.author+'</div></div>');

	$("#firmware-list #list").append($item)

	$item.click(function() {
		$(".item").removeClass("selected");
		$(this).addClass("selected");
		var $div = $("#firmware-upload-section #action");
	
		$div.fadeOut("500", function() {
			$div.find(".name").text(obj.name);
			$div.find(".author").text(obj.author);
			$div.find(".source a").attr("href", obj.source);
			$(this).fadeIn("500");
		});

		$div.find("#upload").click(function() {
			
			if (isRemote) {
				download_firmware(obj, function(isOk, local_path) {
					if (isOk) upload_firmware(local_path);
				});
			} else {
				upload_firmware(file_url, "/dev/sdb");	
			}
		});
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


function download_firmware(obj, callback) {
	if (!fs.existsSync("./tmp")){
    		fs.mkdirSync("./tmp");
	}

	var from = get_remote_firmware_url(obj.name);
	var to = process.cwd() + "/tmp/" + obj.name+".bin";
	//console.log("saving from: "+ from);
	//console.log("saving to " + to );

	httpreq.download(from, to
	, function (err, progress){
	    if (err) return console.log(err);
	    //console.log("downloading from " + progress);
	}, function (err, res){
	    if (err) return console.log(err);
	    //console.log(res);
	    var md5result;
            fs.readFile(to, function(err, buf) {
			if (md5(buf) == obj.md5) {
				//console.log("md5 ok");
				md5result = true;
			} else {	
				//console.log("md5 nop");
				md5result = false;
			}
			callback(md5result, to);
	    }); //readfile
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

function bind_drag_and_drop_area() {
	var holder = document.getElementById('board');
	holder.ondragover = function () { this.className = 'hover'; return false; };
	holder.ondragleave = function () { this.className = ''; return false; };
	holder.ondrop = function (e) {
	  e.preventDefault();

	  for (var i = 0; i < e.dataTransfer.files.length; ++i) {
	    upload_firmware(e.dataTransfer.files[i].path);
	  }
	  return false;
	};
}


function hide_all_sections() {
	$("#main #editor-container").hide();

} 

function show_section() {
	

}

//interval of given delay, will execute callback with [true] or [false] as param
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
