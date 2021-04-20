/**
 * 
 * solution found in a stackoverflow topic
 * 
 * @author pery mimon
 * @link https://stackoverflow.com/questions/4576694/saving-and-restoring-caret-position-for-contenteditable-div
 */

function saveCaretPosition(context){
    var selection = window.getSelection();

    if (!selection.rangeCount) {
        return () => {};
    }

    var range = selection.getRangeAt(0);
    range.setStart(context, 0);
    var len = range.toString().length;

    return function restore(){
        var pos = getTextNodeAtPosition(context, len);
        selection.removeAllRanges();
        var range = new Range();
        range.setStart(pos.node ,pos.position);
        selection.addRange(range);

    }
}

function getTextNodeAtPosition(root, index){
    const NODE_TYPE = NodeFilter.SHOW_TEXT;
    var treeWalker = document.createTreeWalker(root, NODE_TYPE, function next(elem) {
        if(index > elem.textContent.length){
            index -= elem.textContent.length;
            return NodeFilter.FILTER_REJECT
        }
        return NodeFilter.FILTER_ACCEPT;
    });
    var c = treeWalker.nextNode();
    return {
        node: c? c: root,
        position: index
    };
}