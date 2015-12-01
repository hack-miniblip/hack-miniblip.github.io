/*
Miniblip firmware loader
by @demiurgosoft
*/



var exec = require('child_process').exec;
var portNames = ["CRP DISABLD", "MINIBLIP"]; //possible search names for miniblip port


//search all connected
function search_port(callback) {
	var cmd = "mount|grep -E \"" + portNames.join("|") + "\" | grep -Eo \"^[^ ]+\"";
	exec(cmd, function(err, stdout, stderr) {
		if (err) callback(err);
		else callback(stderr, stdout.replace(/\n$/, "").split("\n"));
	});
}

//loads given firmware
function load_firmware(firmware_path, done) {
	search_port(function(err, res) {
		if(err || !res || res.length===0) return done(new Error("Miniblip not found"));
		var cmd = "sudo dd if=" + firmware_path + " of=" + res[0] + " bs=512 seek=4 conv=notrunc";
		exec(cmd, function(err, stdout, stderr) {
			if (err) return done(err);
			else {
				exec("sudo umount " + res[0], function(err, stdout, stderr) {
					return done(err);
				});
			}
		});
	});
}

 //Usage example
/*load_firmware("rainbow.bin", function(err) {
	if (err) console.log("Error Loading");
	else console.log("Load Finished");
});*/


//to use with require, uncomment
//module.exports=load_firmware;
