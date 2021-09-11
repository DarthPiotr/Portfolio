var msg = "bonus";
var task = setInterval(function(){
    var btns = document.querySelector('div[data-test-selector=chat-input-buttons-container]').getElementsByTagName('button');
    for(var i = 0; i < btns.length; i++){
        if(btns[i].closest('div').innerHTML.search(msg) != -1){            
            btns[i].click();
            console.log("Reward claimed!");
            break;
        }
    }
}, 1000);