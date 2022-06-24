<h1>Detectarea de coliziuni între cercuri</h1>

<h2>1. Coliziune</h2>
<hr>
<h3>1.1 Definiție și paradigmă</h3>
<p>
 Când aducem în discuție termenul de coliziune, ne referim la ciocnirea de forțe sau la tangența dintre obiecte care se mișcă unul spre altul.
 </p>
<h3>1.2 Context informatic</h3>
<p>
În ceea ce privește domeniul informatic, importanța deosebită pe care o are un sistem de detectare a coliziunilor poate fi pusă în evidență în simulări pentru sisteme fizice, de exemplu, sau în cadrul jocurilor video, unde detectarea de coliziuni și rezolvarea lor implică o cărămidă solidă în obținerea unui produs ce poate fi, în primul rând, jucat.
 </p>
 
 <h2>2. Eficiență</h2>
 <hr>
 <h3>2.1 Probleme</h3>
<p>
Alegând arbitrar un spațiu dreptunghiular și 100 de obiecte care îl populează, putem spune că, pentru verificarea tuturor coliziunilor dintre obiectele , este necesar să realizăm aproximativ 10000 de operații, fiecare obiect cu fiecare dintre celelalte din jur. Acest fapt aduce cu sine problema de eficiență a verificării coliziunilor în timp pătratic. Imaginându-ne că într-un joc video, luând exemplul anterior, numărul de obiecte cu care jucătorul interacționează, dar și numărul altor entități care se deplasează și necesită operația de verificare a coliziunilor, depășește rapid ordinul miilor, astfel că o soluție pătratică nu poate fi pusă în practică fără pierderi masive în performanță.
</p>
 <h3>2.2 Soluții</h3>
<p>
  O soluție comună în rândul programatorilor o constituie partiționarea spațiului inițial. Motivul din spatele acestei metode de diminuare a numărului de operații este intuitiv: două obiecte aflate la capete opuse ale unui spațiu sau sub-spațiu nu se ating, drept urmare, nu este necesară operația de verificare între obiecte aflate la distanțe mari unul de celălalt. Această separare a spațiului se poate realiza folosind o structură de  de tip <i>quadtree</i>.
 </p>
 
  <h2>3. Quadtree</h2>
  <hr>
  <h3>3.1 Definiție și paradigmă</h3>
  <p>
  Un <i>quadtree</i> este o structură de  care codifică un spațiu bidimensional în celule adaptabile sau ajustabile din punct de vedere al mărimii. Asemănător cu arborii binari, <i>quadtrees</i> sunt arbori în care fiecare nod care nu reprezintă o frunză va avea patru copii.
  </p>
  <h3>3.2 Partiționare prin cadrane</h3>
  <p>
 În general, un <i>quadtree</i> este reprezentat grafic asemenea unei tabele, fiecare celulă a acesteia reprezentând unul dintre noduri. Orice <i>quadtree</i> începe cu un singur nod, urmând ca mai apoi să se adauge mai multe pe măsură ce crește numărul de obiecte. La partiționare, fiecare obiect va fi încadrat în unul dintre cei 4 copii ai nodului curent. Orice obiect care nu se încadrează complet în interiorul unui nod, sau careu, va fi plasat în nodul părinte zonei nou partiționate. Fiecare nod, sau careu, se va subdiviza la rândul său, pe măsură ce sunt adăugate obiecte.
  </p>
  
 <h2>4. Implementarea arborelui</h2>
  <hr> 
  <h3>4.1 Câmpuri și metode folosite</h3>
  <p>
  În ceea ce privește detaliile de implementare, arborele cuprinde drept câmpuri private un număr maxim de obiecte, o variabilă booleană care reține dacă un nod se împarte la rândul său, un vector de noduri, un vector de cercuri și un dreptunghi, definit de coordonatele unui colț și lungimile laturilor. Metodele folosite sunt cele de inserare, ștergere, împărțire, ștergere completă și de afișare grafică. De menționat este faptul că dreptunghiul cuprinde și o metodă care verifică dacă un cerc arbitrar ales este sau nu aflat în interiorul lui.
  </p>
  <h3>4.2 Constructori</h3>
  Constructorul <i>quadtree</i>-ului setează un număr maxim de obiecte egal cu 10, inițializează cu <i>false</i> valoarea variabilei care ține cont dacă un nod este sau nu împărțit în sub-noduri și desemnează coordonatele primul dreptunghi. Constructorul dreptunghiului pune implicit coordonatele colțului pe poziția (0; 0) și consideră lungimea ambelor laturi egală cu 1. 
  <h3>4.3 Metode</h3>
  <h4>4.3.1 Verificarea dacă un cerc este într-un dreptunghi</h4>
  <p>
  Pentru realizarea acestei funcții, am folosit drept fundament matematic <i>AABB</i>-ul, abreviere pentru <i>axis aligned bounding box</i>. Pe scurt, am calculat coordonatele punctelor care împart laturile dreptunghiului curent în jumătate, iar apoi coordonatele centrului acestuia. Am salvat, ulterior, diferența dintre coordonatele centrului dreptunghiului și cele ale cercului dat ca parametru, definit prin coordonatele centrului și lungimea razei. Urmează să salvăm și diferența, pe coordonate, dintre centrul cercului dat și centrul dreptunghiului curent. Mai departe, am folosit ceea ce se numește \textit{clamping}, metodă ce restricționează o valoare numerică într-un interval dat de alte două. În cazul de față, folosim această metoda a afla cel mai apropiat punct al dreptunghiului de centrul cercului. Funcția va returna dacă distanța euclidiană de la cel mai apropiat punct al dreptunghiului de cerc este mai mica sau egala cu raza.
  </p>
  <h4>4.3.3 Inserare</h4>
  <p>
  Tocmai pentru eficientizarea prin partiționarea spațiului, prima verificare, înainte de a realiza orice inserare, se rezumă la a vedea dacă cercul de inserat intră sau nu în dreptunghiul curent.
</p>
<p>
În caz afirmativ, putem verifica dacă nodul curent nu a fost împărțit până la acest moment, iar sub-arborele admite încă inserări, nedepășind limita superioară menționată drept câmp privat, mai sus. Dacă aceste condiții sunt respectate, se poate pune cercul curent în vectorul de cercuri și se poate realiza verificarea dacă cercul curent se intersectează cu oricare altul din sub-arborele în care se află. Această verificare se folosește de distanța euclidiana dintre centrele cercurilor verificate. Dacă aceasta este mai mică sau egala decât suma razelor cercurilor analizate, înseamnă că cercurile pot fi adăugate într-un vector de perechi de cercuri care realizează coliziune. 
</p>
<p>
În cazul în care condițiile enumerate în paragraful anterior nu sunt respectate, se realizează o împărțire a sub-spațiului, iar fiecare nod va apela recursiv funcția de inserare pentru a se reîncerca distribuirea sub-spațiilor.
  </p>
  <h4>4.3.4 Împărțire</h4>
  <p>
  Împărțirea se realizează cunoscând coordonatele sub-spațiului curent. Cu ajutorul lor, putem obține lungimea și lățimea noului sub-spațiu, egale cu jumătate din cele ale sub-spațiului acum partiționat. Urmează a se pune în vectorul de noduri patru noi noduri, care reprezintă la rândul lor dreptunghiuri.

În final, se inserează din nou cercurile, pentru fiecare nod, se șterg elementele din vectorul de cercuri, iar spațiul curent este considerat acum partiționat.
  </p>
  <h4>4.3.5 Ștergere</h4>
  <p>
Ștergerea începe identic cu inserarea, întrucât este necesar sa cunoaștem dacă cercul este sau nu încadrat în nodul, sau sub-spațiul, curent. Dacă sub-spațiul curent nu mai este partiționat, sau în alți termeni, dacă nodul curent este frunză, atunci putem parcurge cercurile prezente în acel sub-spațiu și îl putem șterge pe cel dorit. Altfel, dacă spațiul curent este partiționat, continuăm căutarea pe alt sub-nod.
  </p>
  
  <h4>4.3.6 Afișare grafică</h4>
  <p>
Pentru <i>output</i>-ul grafic am folosit biblioteca <i>olcPixelGameEngine.h</i>, ce permite cu ușurință să desenăm figuri geometrice, linii și segmente sau să scriem text. În contextul acestei funcții, am afișat pentru fiecare nod spațiul pe care îl acoperă, precum și numărul de cercuri din fiecare careu.
  </p>
  
  <h4>4.3.7 Ștergere completă</h4>
  <p>
Dacă avem un sub-spațiu partiționat, apelăm funcția de ștergere completă recursiv, până la întâlnirea primei frunze, sau a primului sub-spațiu copil al spațiului de la care am pornit. Pentru acesta, ștergem toate nodurile și toate cercurile din interior, după care, la reapel, după ștergerea tuturor celor patru copii, nodul curent devine nepartiționat.
  </p>
  
   <h2>5. Implementarea obiectelor</h2>
  <hr> 
  <p>
Orice obiect deriva din clasa <i>circle.h</i> care are ca și câmpuri private coordonatele centrului, viteză, accelerație, unghi și rază. Obiectele traversează ecranul de la dreapta la stânga, pornind de la o coordonata aleatorie de pe ecran, cu o viteză intre 1 și 15 și unghi inițial 0. O variabilă ce va ține minte rotația va defini unghiul în funcția de <i>update</i>. La viteza inițială, la fiecare apel al funcției de <i>update</i>, se adună timpul înmulțit cu accelerația. Coordonatele centrului se actualizează și ele, împreună cu unghiul, iar accelerația devine 0.
  </p>
  
  <h2>6. Aplicație</h2>
  <hr> 
  <h3>6.1 Prezentare</h3>
  <p>
Aplicația urmărește punerea în evidență a coliziunilor dintre cercuri care traversează ecranul de la stânga la dreapta, fiind vizibile totodată spațiile partiționate și numărul de cercuri care le populează. Între oricare două cercuri tangente se trasează o linie, pentru ilustrarea coliziunii. 
  </p>
  <h3>6.2 Implementare</h3>
  <p>
Funcțiile de <i>OnUserCreate()</i> și <i>OnUserUpdate()</i> fac parte din biblioteca <i>olcPixelGameEngine.h</i> și se referă la generarea condițiilor de start ale aplicației și, respectiv, continuarea și alterarea condițiilor în ciclu infinit. Pentru a modifica în clasa aplicației aceste metode, am utilizat funcționalitatea de <i>override</i> din C++. 
  </p>
  <p>
  Funcția de <i>OnUserCreate()</i> creează primul arborele cu nodul inițial și resetează datele: șterge toate obiectele, distruge toate nodurile, realizează un <i>random seed</i> și generează 100 de obiecte noi, pe care le adaugă în vectorul de obiecte și le inserează în arbore.
  </p>
  
  <p>
  Funcția de <i>OnUserUpdate()</i> setează fundalul negru, șterge elementele din vectorul care reține elementele aflate la un moment dat în coliziune, șterge arborele și, pentru fiecare obiect din șirul de obiecte, se realizează o inserare în arbore, o deplasare a coordonatelor și un apel al funcției <i>DrawCircle()</i> pentru afișarea grafică a cercului. Se scrie, totodată, pe ecran, numărul de elemente aflate în coliziune, iar pentru fiecare pereche de obiecte din șirul de obiecte tangente, se desenează o linie galbenă între centrul primului cerc și centrul cercului de-al doilea.
  </p>
  
  <h2>7. Posibilități de expansiune</h2>
  <hr>
  <p>
  Orice proiect are o posibilitate de a fi continuat spre a atinge noi limite de performanță sau noi funcționalități. Proiectul discutat în această lucrare poate fi extins pe mai să rezolve problemele ce apar la coliziune, prin introducerea unui sistem de forțe fizice. Totodată, se pot realiza operații de verificare a coliziunii pentru orice forma geometrică. Sistemul creat poate fi folosit cu ușurință și în realizarea unui joc video de tip arcade, precum un <i>space shooter</i> sau <i>PAC-MAN</i>.
  </p>
  
  <h2>8. Concluzii</h2>
  <hr>
  <p>
  Câteva dintre concluziile pe care le putem extrage se referă la eficiența acestei metode de analizare a coliziunilor. Putem realiza rapid că numărul de careuri influențează numărul de operații de verificare. Dacă numărul de careuri este mai mic, atunci este folosită mai puțină memorie. Implicit, în această situație, numărul de verificări este mai mare. Invers, dacă numărul de careuri este considerabil mai mare, numărul de operații de verificare scade, dar memoria consumată este mai mare. Un dezavantaj al împărțirii pe foarte multe careuri îl reprezintă numărul mare de noduri care sunt goale, adică nu cuprind niciun cerc, întrucât acestea reprezintă o risipă de memorie. 
  </p>
   <p>
  O altă concluzie extrasă se referă la modalitățile prin care se pot realiza aceste probleme de coliziuni. <i>Quadtree</i>-ul nu reprezintă singura structură de date eficientă pentru gestionarea partiționării spațiului bidimensional. O variantă alternativă o reprezintă un <i>K-D tree</i> care partiționează neuniform, sortând elementele după una dintre axe și trasând o axă mediană intre cele două obiecte aflate la mijlocul șirului sortat. Procedeul se repetă și pentru axa opusă și se va termina atunci când este atins numărul maxim de obiecte dintr-un careu sau, mai eficient, când cat mai multe careuri cuprind un singur obiect, astfel încât pentru multe dintre acestea să nu se mai realizeze operația de verificare.
  </p>
   <p>
  Se poate aminti, totodată, faptul că problema coliziunilor rămâne una de importanță deosebită cu cât numărul de cadre pe secunda, sau <i>FPS</i>, este mai mic. În detectarea coliziunilor, cât și în rezolvarea lor, dacă viteza unui obiect este foarte mare și <i>FPS</i>-ul mic, se poate ca obiectul în mișcare, la următoarea etapă a procesului de <i>rendering</i>, să iasă din limitele prestabilite și să intre într-un alt obiect sau să treacă prin el fără detectarea coliziunii. Astfel de probleme țin deja de etapa propriu-zisă de <i>rendering</i>, dar eficiența sistemului de <i>rendering</i> influențează direct calitatea calculului de coliziune.
  </p>
   <p>
  Un alt aspect extras din procesul de documentare, împreună cu lucrul propriu-zis la acest proiect, îl reprezintă fundamentele matematice pe care se bazează detectarea de coliziuni. Dacă între cercuri sau poligoane convexe funcționează cu succes calcularea proiecțiilor punctelor pe axe și verificarea dacă acestea se încadrează în intervalul punctelor definit de unul dintre ele sau calculul intersecției diagonalelor, la poligoane concave apar numeroase probleme mai greu de rezolvat.
  </p>
  <h2>9. Referințe</h2>
  <hr>
  <p>
  Pentru implementarea structurii de date, am folosit informațiile prezentate în următorul articol: <a href="https://gamedevelopment.tutsplus.com/tutorials/quick-tip-use-quadtrees-to-detect-likely-collisions-in-2d-space--gamedev-374"> Quick Tip: Use Quadtrees to Detect Likely Collisions in 2D Space </a>
  </p>
  
  <p>
  Pentru informațiile despre <i>K-D tree</i>, am folosit drept suport următorul videoclip: <a href="https://www.youtube.com/watch?v=eED4bSkYCB8&list=PLUbJ2XXJWc4aKu7iT4Vz4vfaZ6I3vZ3IU&index=43&t=1182s"> Building Collision Simulations: An Introduction to Computer Graphics </a>
  </p>
  
  <p>
  Suportul matematic discutat provine din videoclipul următor: <a href="https://www.youtube.com/watch?v=7Ik2vowGcU0"> Convex Polygon Collisions #1 </a> și din articolul: <a href="https://learnopengl.com/In-Practice/2D-Game/Collisions/Collision-Detection"> Collision detection </a>
  </p>
