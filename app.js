
var pos=[];
var neg=[];
var ws = new WebSocket( "ws://" + location.host
			, "arduino"
			, null );

ws.onopen = function() {
}

ws.onclose = function() {
    ws = new WebSocket( "ws://" + location.host
			, "arduino"
			, null );
}

for( var i = 0; i < 20; i++ ) {
	const istr = ( i < 10?"0"+i:i );
	pos.push( document.getElementById( "p" + (i+1) ) );
        pos[i].addEventListener( "click", ()=>{
        	ws.send( "P" + istr );
        });
	neg.push( document.getElementById( "n" + (i+1) ) );
        neg[i].addEventListener( "click", ()=>{
        	ws.send( "N" + istr );
        });
}



