
let ss = ''
let page_number = 0
let URLL = ""


for ( int i = 0; i <= 10; i++ ) {

	let ss = ''
	let page_number = 0
	let URLL = ""

	Array.from($('ul.content li')).forEach((li) => {
		url = li.getElementsByTagName('a')[0].href

		{
			let xhr = new XMLHttpRequest();
			xhr.onreadystatechange = function () {
				 if (xhr.responseURL.includes(ss)) {		 	
			  		console.log("DAAAAAAAAAAAAAAAAA " + xhr.responseURL);
				 }
			};

			xhr.open('HEAD', url, true);
			xhr.send(null);
		}
		{
			let xhr = new XMLHttpRequest();
			xhr.onreadystatechange = function () {
				 if (xhr.responseURL.includes(ss)) {		 	
			  		console.log("DAAAAAAAAAAAAAAAAA " + xhr.responseURL);
				 }
			};

			xhr.open('HEAD', url, true);
			xhr.send(null);
		}
	})

	page_number += 1
	window.location.href = URLL + i + "/"
	sleep(1000);
}

function sleep(milliseconds) {
  var start = new Date().getTime();
  for (var i = 0; i < 1e7; i++) {
    if ((new Date().getTime() - start) > milliseconds){
      break;
    }
  }
}


clearTimeout(timerID)


Array.from($('ul.content li')).forEach((li) => {

try {    
    Http.open("GET", url, false);
    Http.send();
    if (Http.responseURL.contains(ss) )
    	alert(Http.responseURL)
}
catch(e) {}


{
	let xhr = new XMLHttpRequest();
	xhr.onreadystatechange = function () {
		 if (this.readyState === this.DONE)
	  		console.log(xhr.responseURL);
	};

	xhr.open('HEAD', url, true);
	xhr.send(null);
}
{
	let xhr = new XMLHttpRequest();
	xhr.onreadystatechange = function () {
		 if (this.readyState === this.DONE)
	  		console.log(xhr.responseURL);
	};

	xhr.open('HEAD', url2, true);
	xhr.send(null);
}
