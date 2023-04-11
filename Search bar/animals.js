// JavaScript code
function search_animal() {
    let input = document.getElementById('searchbar').value
    console.log(input);
    // print(input) this command prints webpage
    input = input.toLowerCase();
    let x = document.getElementsByClassName('animals');
    console.log(x);
    // print(x) this is for print page
    //yaha pr data structure kaam ayega na dost
    
    for (i = 0; i < x.length; i++) {
        if (!x[i].innerHTML.toLowerCase().includes(input)) {
            x[i].style.display = "none";
        }
        else {
            x[i].style.display = "list-item";
        }
    }
}
