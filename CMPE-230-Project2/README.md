This project was designed to take the data of the intervals given by user on the terminal and list the prepared infomations in csv format
You can run the python file on terminal and type the interval like 2018-Fall 2019-Spring after that the proragram would give you the list of all the deparment names undergraduate and graduate classes classified into every semester

Sermesters are Fall, Spring and Summer

In order to run the code you need to type bucourses.py interval1 interval2 like bucourses.py 2018-Fall 2019-Spring

Some Assumptions:
- You assume starting and ending semesters will be different in inputs.
- You assume course codes without digits (like SFL) are undergraduate.
External Libraries:
- I used urllib.request, re(regexp module) and BeautifulSoup for handling requests from Web and
HTML.
Implementation:
- I wrote a geturl function that takes a semester and a department and return the urllib
using regular expressions
- I wrote a download_info function that takes an url and returns the necessary information about
courses as sets and dictionaries.
I used BeautifulSoup here to take necessary data from HTML tables.
- I embedded the department names and codes to our program with a list and a dictionary.
- I took the input string from console and parsed it to find start and end semesters, then created a list
that contains all semesters between
start and end semesters.
- For every semester and every department we called the download_info function, while doing this
we computed number of courses and instructors for every semester, put the course names for every
department codes
into firstblock dictionary, and put all the information to lastmission dictionary. We handle departments
that have two long names(like ASIA)
and the departments with a unique long name differently here.
- At the last stage, we iterate over all departments, computing their number of courses(grad and
undergrad) and distinct instructors by looking at firstblock
and lastmission dictionaries and print all the course information in CSV.
