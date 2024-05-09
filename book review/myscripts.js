// Import required Firebase services
import { initializeApp } from
"https://www.gstatic.com/firebasejs/9.18.0/firebase-app.js";
import { Firestore,
getFirestore,
onSnapshot,
query,
collection,
orderBy,
addDoc } from
'https://www.gstatic.com/firebasejs/9.18.0/firebase-firestore.js'
// Your web app's Firebase configuration
const firebaseConfig = {
    apiKey: "AIzaSyB9P1akYdqGbnUdYzV-FOSJtDlmcbqQl2A",
    authDomain: "cs022-2358830-sumitshah.firebaseapp.com",
    projectId: "cs022-2358830-sumitshah",
    storageBucket: "cs022-2358830-sumitshah.appspot.com",
    messagingSenderId: "225477100760",
    appId: "1:225477100760:web:bac46662a971359af343ad"
  };
// Initialize Firebase
const app = initializeApp(firebaseConfig);
const db = getFirestore(app);

// Get a live data snapshot (i.e. auto-refresh) of our Reviews collection
const q = query(collection(db, "Reviews"), orderBy("book_name"));
const unsubscribe = onSnapshot(q, (snapshot) => {
// Empty HTML table
$('#reviewList').empty();
// Loop through snapshot data and add to HTML table
var tableRows = '';
snapshot.forEach((doc) => {
tableRows += '<tr>';
tableRows += '<td>' + doc.data().book_name + '</td>';
tableRows += '<td>' + doc.data().book_rating + '/5</td>';
tableRows += '</tr>';
});
$('#reviewList').append(tableRows);
// Display review count
$('#mainTitle').html(snapshot.size + " book reviews in the list");
});
