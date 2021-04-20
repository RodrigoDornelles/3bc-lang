document.getElementById("ide-editor").addEventListener("input", function() {
    let cursorReset = saveCaretPosition(this);
    let lines = this.textContent.split("\n");

    for (let index = 0; index < lines.length; index++) {
        lines[index] = addComments(lines[index]);
    }

    this.innerHTML = lines.join("\n");
    cursorReset(); 
}, false);

function addComments(line)
{
    let start = line.indexOf("#");
    let end = line.length; 

    if (start != -1) {
        let old_line = line;
        line = old_line.slice(0, start);
        line += '<span class="comment">';
        line += old_line.slice(start, end);
        line += '</span>';
    }

    return line;
}