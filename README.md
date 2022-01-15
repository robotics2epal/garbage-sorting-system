# garbage-sorting-system

<h3 align= left>Σύστημα διαλογής υλικών (Μέταλλο, γυαλί, πλαστικό)</h3>

<h2 align= center>Έργο για συμμετοχή στο 4ο Πανελλήνιο Διαγωνισμό Ανοιχτών Τεχνολογιών στην Εκπαίδευση: Κυκλική Οικονομία</h2>

<hr>
Η ομάδα ρομποτικής του σχολείου μας 2ο ΕΠΑΛ / ΕΚ Αγρινίου προτείνει ένα σύστημα ανακύκλωσης μέσω του οποίου θα μπορούμε να κάνουμε καλύτερη διαλογή των υλικών. Η πρότασή μας είναι η εξής. Να διαχωριστεί το χαρτί από τα υπόλοιπα ανακυκλώσιμα υλικά (μέταλλο, γυαλί, πλαστικό) γνωστούς κάδους μπλε και να μπει σε τρίτο κάδο π.χ. καφέ. 

Η υλοποίηση που προτείνουμε περιλαμβάνει ένα σύστημα διαλογής των υλικών που θα συλλέγονται στους μπλε κάδους. 

Θα δημιουργηθεί από ένα 3d εκτυπωτή ένας “πύργος” μέσα στον οποίο θα μπαίνουν τα υλικά. Καθώς θα προχωράνε προς τα κάτω θα περνούν μπροστά από αισθητήρες και με χρήση κινητήρων θα οδηγούνται στους κάδους. Έτσι 
•	θα εντοπίζονται τα μέταλλα και θα διαχωρίζονται στο πρώτο κάδο. 
•	στην συνέχεια το γυαλί θα τοποθετείται σε δεύτερο κάδο. 
•	το υλικό που θα περισσεύσει θα είναι το πλαστικό, όπου και αυτό με τη σειρά του θα το τοποθετείται σε ξεχωριστό κάδο.

<b>Σημειώσεις.</b>
1.	Η κλίμακα θα μικρότερη του κανονικού. 
2.	Τα υλικά θα έχουν το ίδιο μέγεθος για λόγους ομοιομορφίας.
3.	Επειδή η ενασχόληση με γυαλί ενέχει κινδύνους για τους μαθητές, θα χρησιμοποιήσουμε ιδιότητες που έχει το plexiglass και είναι παρόμοιες.


Όλη η κατασκευή θα υποστηρίζεται ενεργειακά από έναν Solar tracker ο οποίος θα κινεί φωτοβολταϊκό το οποίο : 
•	θα ακολουθεί τη πορεία του ήλιου
•	όταν νυχτώσει θα επιστρέφει στην ανατολή για να είναι έτοιμος της επόμενη ημέρα
•	όλα τα μέρη θα εκτυπωθούν από 3d εκτυπωτή



<n>Υλικά που θα χρειαστούμε </b>

Για διαλογέα 
•	NodeMCU - Lua based ESP8266
•	Stepper Driver Breakout - ULN2003
•	Stepper Motor
•	Led Διάφανο 10mm Λευκό
•	LED Diffused 10mm Κόκκινο
•	LED Diffused 10mm Πράσινο
•	Φωτοαντίσταση LDR 
•	Led Holder 10mm Plastic

Για τον Solar Tracker

•	Φωτοβολταϊκή Κυψέλη
•	Μπαταρία με φορτιστή
•	ρουλεμάν
•	NodeMCU - Lua based ESP8266
•	Servo Motor
 
Και για τα δύο
•	Ribbon 40wire 20cm - Female to Female
•	Ribbon 40wire 20cm - Female to Μale
•	Ribbon 40wire 20cm - Male to Male
•	Νήμα PLA 1.75mm
•	Πλακέτα Δοκιμών 400 Οπές - Άσπρη
•	Πλακέτα Δοκιμών Mini - Μπλέ
