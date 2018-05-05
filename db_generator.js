var fs = require('fs');

var array ;
var logger = fs.createWriteStream('log.txt', {
  flags: 'a' 
})

fs.readFile('object.txt', 'utf8', function (err,data) {
    if(err) throw err;
    array = data.toString().split("\n");
    for(i in array) {
		array[i] = array[i].trim();
		var num  = mp.joaat(array[i]);
		var n = num.toString();
		array[i] += "\n";
		n += " ";
		n += array[i];
		logger.write(n);
		console.log(array[i]);	
    }
});