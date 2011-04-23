// I do not know how to parse the command line, so regex are hard coded.

var r = [ /([a-zA-Z][a-zA-Z0-9]*):\/\/([^ /]+)(\/[^ ]*)?/,
		  /([^ @]+)@([^ @]+)/,
		  /([0-9][0-9]?)\/([0-9][0-9]?)\/([0-9][0-9]([0-9][0-9])?)/,
		  /([a-zA-Z][a-zA-Z0-9]*):\/\/([^ \/]+)(\/[^ ]*)?|([^ @]+)@([^ @]+)/
		];

while ((l = readline()) != null)
	if (l.match(r[3])) // change this line to change regex
		print(l)

