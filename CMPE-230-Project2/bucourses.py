#!/usr/bin/env python3
# -- coding: utf-8 --
import urllib.request
import re
import sys
from bs4 import BeautifulSoup


def geturl(year, deparmanttemp):
    #this part the create the url we would download
    gate = urllib.request
    #deparmanttemp[0] is the long name lime COMPUTER ENGINEERING
    # deparmanttemp[1] is the code of the department
    deparmant = deparmanttemp[0]
    kısaad = deparmanttemp[1]
    # the site of bounregistration ahs like the style if we have space we replace it with +
    # if we have : then we replace it with %3a then just like the other if we have & we replace it with %26
    deparmant = re.sub(" ", "+", deparmant)
    deparmant = re.sub(":", "%3a", deparmant)
    deparmant = re.sub(",", "%2c", deparmant)
    deparmant = re.sub("&", "%26", deparmant)
    # then we create it the url and return it
    url = "https://registration.boun.edu.tr/scripts/sch.asp?donem=" + \
        year+"&kisaadi="+kısaad+"&bolum="+deparmant
    return url



def download_info(urltodownload):
    # we are taking the url adress and dowlnload the information here.
    # we use urllib which is module of python3
    req = urllib.request
    connection = req.urlopen(urltodownload)
    # we use BeautifulSoup to take the table informations
    soup = BeautifulSoup(connection.read(), "html.parser")

    data = soup.find_all("table", {"border": "1"})
    # we create a hoca_set to take the all instr of a season of a departmant like CMPE-2016-FALL
    hoca_set=set()
    # We create a set called thenameofdep_set to store all the long name of courses
    thenameofdep_set = set()
    # We create a set called thename_dep_set to store all the code of courses like cmpe140 cmpe 150
    thename_dep_set = set()
    # the x y z are the standard index of the code of class the name of class and the instr of class consecutively
    x=0
    y=2
    z=5
    # we have a inside dic to store a dic 3 set
    inside={}
    if(len(data)>0):
        if(len(data[0])>=1):
            #in first row we create a look to determine which colomn is stroing instr because in 2019-Summer-3 the index is 6 but the other may have the index as a 5
            veri = data[0].find_all("tr")
            virestemp2 = veri[0].find_all("td")
            a=0
            # when we find the index a ,we assign it to the z
            for i in virestemp2:
                if(i.text=="Instr."):
                    z=a
                a=a+1
            for N in range(1, len(veri)):
                # we now consider the second row and the rest of it
                # they all consist of the main course name vs
                # we find them by using find_all("td") and take the values which is considered as text
                virestemp = veri[N].find_all("td")
                classcodex = (virestemp[x].text)
                classname = (virestemp[y].text)
                instrutorname = (virestemp[z].text)
                # if there is a lab or ps the first row could be empty and we have an error so by using this if(len(classcodex)>=3): we only have the main courses
                if(len(classcodex)>=3):
                    # if there are a space like CMPE 140 we create a CMPE140
                    classcodex=re.sub(" ","",classcodex)
                    # we erease the last 3 digit composed of . , and section number like CMPE140.01 -> CMPE140
                    thename=classcodex[:len(classcodex)-4]
                    # We add it into the set we create
                    thename_dep_set.add(thename)
                    # we delete the last char beceuse it is /ax and we dont consider it
                    classname=(classname[0:(len(classname)-1)])
                    #if there is a , it could be an error forcvs files so we replace it with ;
                    classname=re.sub(",",":",classname)
                    instrutorname = instrutorname[0:(len(instrutorname)-1)]
                    hoca_set.add(instrutorname)
                    thenameofdep_set.add(classname)
                    # if it is not STAFF STAFF We add the instrutorname
                    if(instrutorname!="STAFF STAFF"):
                        try:
                            # this try is important one because if there are severel section we add the inst name in the dic like
                            # CMPE150:{EMRE UGUR, CEMSAY}
                            inside[thename][1].add(instrutorname)
                            #But if there is only one section then the try row give us a error and we only create dic and set the we add the instr to the set
                        except KeyError:
                            inside.update({thename:[classname,{instrutorname}]})
    # if the table is empty then the fuction would return none
    else:
        return None



    # we return the all values we have

    return(inside, thename_dep_set, hoca_set,thenameofdep_set)

#dep_list=[['ELECTRICAL & ELECTRONICS ENGINEERING', 'EE'],['COMPUTER ENGINEERING', 'CMPE'],['MANAGEMENT','AD']]

dep_list = [['ASIAN STUDIES', 'ASIA'], ['ASIAN STUDIES WITH THESIS', 'ASIA'], ['ATATURK INSTITUTE FOR MODERN TURKISH HISTORY', 'ATA'], ['AUTOMOTIVE ENGINEERING', 'AUTO'], ['BIOMEDICAL ENGINEERING', 'BM'], ['BUSINESS INFORMATION SYSTEMS', 'BIS'], ['CHEMICAL ENGINEERING', 'CHE'], ['CHEMISTRY', 'CHEM'], ['CIVIL ENGINEERING', 'CE'], ['COGNITIVE SCIENCE', 'COGS'], ['COMPUTATIONAL SCIENCE & ENGINEERING', 'CSE'], ['COMPUTER EDUCATION & EDUCATIONAL TECHNOLOGY', 'CET'], ['COMPUTER ENGINEERING', 'CMPE'], ['CONFERENCE INTERPRETING', 'INT'], ['CONSTRUCTION ENGINEERING AND MANAGEMENT', 'CEM'], ['CRITICAL AND CULTURAL STUDIES', 'CCS'], ['EARTHQUAKE ENGINEERING', 'EQE'], ['ECONOMICS', 'EC'], ['ECONOMICS AND FINANCE', 'EF'], ['EDUCATIONAL SCIENCES', 'ED'], ['EDUCATIONAL TECHNOLOGY', 'CET'], ['ELECTRICAL & ELECTRONICS ENGINEERING', 'EE'], ['ENGINEERING AND TECHNOLOGY MANAGEMENT', 'ETM'], ['ENVIRONMENTAL SCIENCES', 'ENV'], ['ENVIRONMENTAL TECHNOLOGY', 'ENVT'], ['EXECUTIVE MBA', 'XMBA'], ['FINANCIAL ENGINEERING', 'FE'], ['FINE ARTS', 'PA'], ['FOREIGN LANGUAGE EDUCATION', 'FLED'], ['GEODESY', 'GED'], ['GEOPHYSICS', 'GPH'], ['GUIDANCE & PSYCHOLOGICAL COUNSELING', 'GUID'], ['HISTORY', 'HIST'], ['HUMANITIES COURSES COORDINATOR', 'HUM'], ['INDUSTRIAL ENGINEERING', 'IE'], ['INTERNATIONAL COMPETITION AND TRADE','INCT'], ['INTERNATIONAL RELATIONS:TURKEY,EUROPE AND THE MIDDLE EAST', 'MIR'], ['INTERNATIONAL RELATIONS:TURKEY,EUROPE AND THE MIDDLE EAST WITH THESIS', 'MIR'], ['INTERNATIONAL TRADE', 'INTT'], ['INTERNATIONAL TRADE MANAGEMENT', 'INTT'], ['LEARNING SCIENCES', 'LS'], ['LINGUISTICS', 'LING'], ['MANAGEMENT', 'AD'], ['MANAGEMENT INFORMATION SYSTEMS', 'MIS'], ['MATHEMATICS', 'MATH'], ['MATHEMATICS AND SCIENCE EDUCATION', 'SCED'], ['MECHANICAL ENGINEERING', 'ME'], ['MECHATRONICS ENGINEERING', 'MECA'], ['MOLECULAR BIOLOGY & GENETICS', 'BIO'], ['PHILOSOPHY', 'PHIL'], ['PHYSICAL EDUCATION', 'PE'], ['PHYSICS', 'PHYS'], ['POLITICAL SCIENCE&INTERNATIONAL RELATIONS', 'POLS'], ['PRIMARY EDUCATION', 'PRED'], ['PSYCHOLOGY', 'PSY'], ['SCHOOL OF FOREIGN LANGUAGES', 'YADYOK'], ['SECONDARY SCHOOL SCIENCE AND MATHEMATICS EDUCATION', 'SCED'], ['SOCIAL POLICY WITH THESIS', 'SPL'], ['SOCIOLOGY', 'SOC'], ['SOFTWARE ENGINEERING', 'SWE'], ['SOFTWARE ENGINEERING WITH THESIS', 'SWE'], ['SUSTAINABLE TOURISM MANAGEMENT', 'TRM'], ['SYSTEMS & CONTROL ENGINEERING', 'SCO'], ['TOURISM ADMINISTRATION', 'TRM'], ['TRANSLATION', 'WTR'], ['TRANSLATION AND INTERPRETING STUDIES', 'TR'], ['TURKISH COURSES COORDINATOR', 'TK'], ['TURKISH LANGUAGE & LITERATURE', 'TKL'], ['WESTERN LANGUAGES & LITERATURES', 'LL']]

dep_list_dict={"ASIA":"ASIAN STUDIES","ASIA":"ASIAN STUDIES WITH THESIS","ATA":"ATATURK INSTITUTE FOR MODERN TURKISH HISTORY","AUTO":"AUTOMOTIVE ENGINEERING","BM":"BIOMEDICAL ENGINEERING","BIS":"BUSINESS INFORMATION SYSTEMS","CHE":"CHEMICAL ENGINEERING","CHEM":"CHEMISTRY","CE":"CIVIL ENGINEERING","COGS":"COGNITIVE SCIENCE","CSE":"COMPUTATIONAL SCIENCE & ENGINEERING","CET":"COMPUTER EDUCATION & EDUCATIONAL TECHNOLOGY","CMPE":"COMPUTER ENGINEERING","INT":"CONFERENCE INTERPRETING","CEM":"CONSTRUCTION ENGINEERING AND MANAGEMENT","CCS":"CRITICAL AND CULTURAL STUDIES","EQE":"EARTHQUAKE ENGINEERING","EC":"ECONOMICS","EF":"ECONOMICS AND FINANCE","ED":"EDUCATIONAL SCIENCES","CET":"EDUCATIONAL TECHNOLOGY","EE":"ELECTRICAL & ELECTRONICS ENGINEERING","ETM":"ENGINEERING AND TECHNOLOGY MANAGEMENT","ENV":"ENVIRONMENTAL SCIENCES","ENVT":"ENVIRONMENTAL TECHNOLOGY","XMBA":"EXECUTIVE MBA","FE":"FINANCIAL ENGINEERING","PA":"FINE ARTS","FLED":"FOREIGN LANGUAGE EDUCATION","GED":"GEODESY","GPH":"GEOPHYSICS","GUID":"GUIDANCE & PSYCHOLOGICAL COUNSELING","HIST":"HISTORY","HUM":"HUMANITIES COURSES COORDINATOR","IE":"INDUSTRIAL ENGINEERING","INCT":"INTERNATIONAL COMPETITION AND TRADE","MIR":"INTERNATIONAL RELATIONS:TURKEY,EUROPE AND THE MIDDLE EAST","MIR":"INTERNATIONAL RELATIONS:TURKEY,EUROPE AND THE MIDDLE EAST WITH THESIS","INTT":"INTERNATIONAL TRADE","INTT":"INTERNATIONAL TRADE MANAGEMENT","LS":"LEARNING SCIENCES","LING":"LINGUISTICS","AD":"MANAGEMENT","MIS":"MANAGEMENT INFORMATION SYSTEMS","MATH":"MATHEMATICS","SCED":"MATHEMATICS AND SCIENCE EDUCATION","ME":"MECHANICAL ENGINEERING","MECA":"MECHATRONICS ENGINEERING","BIO":"MOLECULAR BIOLOGY & GENETICS","PHIL":"PHILOSOPHY","PE":"PHYSICAL EDUCATION","PHYS":"PHYSICS","POLS":"POLITICAL SCIENCE&INTERNATIONAL RELATIONS","PRED":"PRIMARY EDUCATION","PSY":"PSYCHOLOGY","YADYOK":"SCHOOL OF FOREIGN LANGUAGES","SCED":"SECONDARY SCHOOL SCIENCE AND MATHEMATICS EDUCATION","SPL":"SOCIAL POLICY WITH THESIS","SOC":"SOCIOLOGY","SWE":"SOFTWARE ENGINEERING","SWE":"SOFTWARE ENGINEERING WITH THESIS","TRM":"SUSTAINABLE TOURISM MANAGEMENT","SCO":"SYSTEMS & CONTROL ENGINEERING","TRM":"TOURISM ADMINISTRATION","WTR":"TRANSLATION","TR":"TRANSLATION AND INTERPRETING STUDIES","TK":"TURKISH COURSES COORDINATOR","TKL":"TURKISH LANGUAGE & LITERATURE","LL":"WESTERN LANGUAGES & LITERATURES"}

# we sort the list as considering their second values
dep_list=sorted(dep_list,key=lambda x:x[1])
firstseason=""
secondseason=""
# we take the inputs and convert it into string
if(len(sys.argv)>1):
    firstseason=str(sys.argv[1])
    secondseason=str(sys.argv[2])
mainstring=firstseason+" "+secondseason
TheNameOfFirstYear=mainstring[0:4]
mainstring=mainstring[5:]
ThesemesterOfFirstYear=""
TheNameOfSecondYear=""
ThesemesterOfSecondYear=""
mainarray=[ThesemesterOfFirstYear,TheNameOfSecondYear,ThesemesterOfSecondYear]
X=0
# we create the all sermester's part like 2018-Fall 2019-Spring in this for loop.We assume the intervals ara different
for N in range(len(mainstring)):
    if(mainstring[N]==" "):
        X=1
    elif(mainstring[N]=="-"):
        X=2
    else:
        mainarray[X]=mainarray[X]+mainstring[N]
mainarray.insert(0,TheNameOfFirstYear)


firstsemester=[mainarray[0],mainarray[1]]
secondsemester=[mainarray[2],mainarray[3]]
tasttodo=[]
tasttodo.append(firstsemester)
x=0
# we create the all season in this while loop at the end of it we would have the all seaons 2018-Fall->2018-2019-1 vs
while(True):
    x=x+1
    temp=tasttodo[len(tasttodo)-1]
    if(temp[1]=="Fall"):
        temp2=[str(int(temp[0])+1),"Spring"]
        tasttodo.append(temp2)
        if(secondsemester==temp2):
            break
    elif(temp[1]=="Spring"):
        temp2=[temp[0],"Summer"]
        tasttodo.append(temp2)
        if(secondsemester==temp2):
            break
    elif(temp[1]=="Summer"):
        temp2=[str(int(temp[0])),"Fall"]
        tasttodo.append(temp2)
        if(secondsemester==temp2):
            break
semester_list=[]
for k in tasttodo:
    if(k[1]=="Fall"):
        temp=k[0]+"/"+str(int(k[0])+1)+"-1"
        semester_list.append(temp)
    elif(k[1]=="Spring"):
        temp=str(int(k[0])-1)+"/"+k[0]+"-2"
        semester_list.append(temp)
    elif(k[1]=="Summer"):
        temp=str(int(k[0])-1)+"/"+k[0]+"-3"
        semester_list.append(temp)
###############################################################################################


lastmission={}
firstblock={}
for semester in semester_list:
    temp={}
    for N in dep_list:
        url = geturl(semester, N)
        gelenlist=download_info(url)

        dersismi=N[1]
        U2=0
        G2=0
        I1=0
        if(gelenlist!=None):

            for i in gelenlist[1]:
                try:
                    if(not isinstance(i,int)):
                        firstblock[dersismi].add(i)
                    bl1=False
                    for digitN in i:
                        if(digitN.isdigit()):
                            if(int(digitN)<=4):
                                U2=U2+1
                                bl1=True
                                break
                            elif(int(digitN)>=5):
                                G2=G2+1
                                bl1=True
                                break
                    if(bl1==False):
                        #print(i)
                        U2=U2+1
                    I1=len(gelenlist[2])
                except ValueError:
                    U2=U2+1
                except KeyError:
                    firstblock.update({dersismi:gelenlist[1]})
            try:
                #this is for special departments have the same code like ASIA
                # if we add the into lastmission[semester] dic createing key like ASIA and once we take and other department whcih has ASIA code then the try code would work and
                # add the values like all intrs'name all department courses long name and codes.Since all of them is set there would not be duplicate names.
                for i in gelenlist[0]:
                    lastmission[semester][dersismi][0][0].update({i:gelenlist[0][i]})
                for i in gelenlist[1]:
                    lastmission[semester][dersismi][0][1].add(i)
                for i in gelenlist[2]:
                    lastmission[semester][dersismi][0][2].add(i)
                for i in gelenlist[3]:
                    lastmission[semester][dersismi][0][3].add(i)
                #in this part we take the eond elemnt off list and add then U2 and G2 values.
                lastmission[semester][dersismi][1][0]=lastmission[semester][dersismi][1][0]+U2
                lastmission[semester][dersismi][1][1]=lastmission[semester][dersismi][1][1]+G2
                # the except part is for the ones that have unique department code like CMPE
            except KeyError:
                temp.update({dersismi:[gelenlist,[U2,G2,I1]]})
            lastmission.update({semester:temp})




# We started to write the table this is the first row
print("Dept./Prog. (name) , Course Code , Course Name,",end="")
for s in semester_list:
    print(s+",",end="")
print("Total Offerings\n")
# we create some boolean variable that we would use later on
ASIA=True
TRM=True
MIR=True
SWE=True
INTT=True
SCED=True
CET=True

# now we iterate the firstblock one by one
for N in firstblock:
    # this boolen variables are to determine if we can go to the progress or not
    # like if the N is ASIA then we only write in just once.Just because we have two department in the dep_list it would write it twice so we create this variables to prohibite it
    # the other variables ending with x are for the ones that only have uniquie department codes
    a=N=="ASIA" and ASIA
    ax=N!="ASIA"
    b=N=="CET" and CET
    bx=N!="CET"
    c=N=="MIR" and MIR
    cx=N!="MIR"
    d=N=="INTT" and INTT
    dx=N!="INTT"
    e=N=="SCED" and SCED
    ex=N!="SCED"
    f=N=="SWE" and SWE
    fx=N!="SWE"
    g=N=="TRM" and TRM
    gx=N!="TRM"
    #(if we are in ASIA CET or the unique deparmant then we can pass the if statement)
    if(a or b or c or d or e or f or g or (ax and bx and cx and dx and ex and fx and gx)):
        # once we take ASIA code then we assign false into the variable ASIA so that we dont go into the ASIA department again because above we bond them
        if(a):
            ASIA=False
        if(b):
            CET=False
        if(c):
            MIR=False
        if(d):
            INTT=False
        if(e):
            SCED=False
        if(f):
            SWE=False
        if(g):
            TRM=False
        # then we are determine the the first column U and G values
        U1=0
        G1=0
        # the the of dersismi is N like CMPE OR AD
        dersismi=N
        # we
        firstblock[dersismi]=sorted(firstblock[dersismi])
        #we iterate the firstblock[dersismi] like firstblock[CMPE] that has the all cmpe class codes
        for code in firstblock[dersismi]:
            try:
                # we have the corse code like cmpe140 then we determine if it is U or G
                bl=False
                for digitN2 in code:
                    if(digitN2.isdigit()):
                        # the char can be int then we chech if it is equal below 4 or not if it is we increase U by 1
                        if(int(digitN2)<=4):
                             U1=U1+1
                             bl=True
                             break
                        # the char can be int then we chech if it is equal below 4 or not if it is we increase U by 1
                        elif(int(digitN2)>=5):
                            G1=G1+1
                            bl=True
                            break
                if(bl==False):
                    U1=U1+1
                        #if none of them is true then we consider it as a undergraduate class
            #if there is a error we consider it as a undergraduate class
            except Exception:
                U1=U1+1
        # now the department that dont have unique department code will be written like this
        if(N=="ASIA" ):
            print("ASIA (ASIAN STUDIES and ASIAN STUDIES WITH THESIS),"+("U"+str(U1)+" "+"G"+str(G1)+" ,,"),end="")

        elif(N=="CET" ):
            print("CET (COMPUTER EDUCATION & EDUCATIONAL TECHNOLOGY and EDUCATIONAL TECHNOLOGY),"+(("U"+str(U1)+" "+"G"+str(G1)+" ,,")),end="")

        elif(N=="MIR" ):
            print("MIR (INTERNATIONAL RELATIONS:TURKEY : EUROPE AND THE MIDDLE EAST and INTERNATIONAL RELATIONS:TURKEY : EUROPE AND THE MIDDLE EAST WITH THESIS),"+(("U"+str(U1)+" "+"G"+str(G1)+" ,,")),end="")

        elif(N=="INTT" ):
            print("INTT (INTERNATIONAL TRADE and  INTERNATIONAL TRADE MANAGEMENT),"+(("U"+str(U1)+" "+"G"+str(G1)+" ,,")))

        elif(N=="SCED" ):
            print("SCED (MATHEMATICS AND SCIENCE EDUCATION and SECONDARY SCHOOL SCIENCE AND MATHEMATICS EDUCATION),"+(("U"+str(U1)+" "+"G"+str(G1)+" ,,")),end="")

        elif(N=="SWE" ):
            print("SWE (SOFTWARE ENGINEERING and SOFTWARE ENGINEERING WITH THESIS),"+("U"+str(U1)+" "+"G"+str(G1)+" ,,"),end="")

        elif(N=="TRM" ):
            print("TRM (SUSTAINABLE TOURISM MANAGEMENT and TOURISM ADMINISTRATION),"+(("U"+str(U1)+" "+"G"+str(G1)+" ,,")),end="")
        # if it is not the special department we write it here.
        # we take the long name of department by using dep_list_dict make the process begin
        else:
            a=re.sub(",",":",dep_list_dict[N])
            print(N+" ("+a+")"+","+("U"+str(U1)+" "+"G"+str(G1)+" ,,"),end="")
        # now we reach out the last column
        totalofferingsU=0
        totalofferingsG=0
        # by iterating all sermester and department we add the U and G values
        for semester in semester_list:
            try:
                a=lastmission[semester][dersismi][1][0]
                totalofferingsU=totalofferingsU+a
                b=lastmission[semester][dersismi][1][1]
                totalofferingsG=totalofferingsG+b
                c=len(lastmission[semester][dersismi][0][2])
                #then assign then into a b c and write it they are for each sermester not for all offerings
                print(("U"+str(a)+" "+"G"+str(b)+" "+"I"+str(c))+", ",end="")
            except Exception:
                print("U0 "+"G0 "+"I0"+",",end="")
            # this part is for all offerings but not having I beucase we dont calculete it yet
        print("U"+str(totalofferingsU)+" "+"G"+str(totalofferingsG),end="")
        hocalar={""}
        hocalar.remove("")
        try:
                    # thiss is to calculete the I part bucause the I part would be the set we add it into hocalar set
            for semestertemp in semester_list:
                for hoca in lastmission[semestertemp][dersismi][0][2]:
                    hocalar.add(hoca)
        # if there is no exception it is okey so we dont have work to do
        except Exception:
            sadsasdasdd=5+9
            #finally we write the I value
        print(" I"+str(len(hocalar)))
        for code in firstblock[dersismi]:
            #in our code beucase of some reason in our set there is a interger 1 and we have a block for it by using this if then we solve he problem but we let it stay
            # because it is always true
            if(not isinstance(code, int)):
                # we create a line list and apend , for the first element
                line=[" ,"]
                # we add the code of the corse like cmpe 140
                line.append(code)
                line.append(",")
                dersname=""
                #dersmane is the long of course name
                #semesterson is to determine the left side of /
                semesterson=0
                # this is a set for the rright side of /
                semesterinstr={""}
                semesterinstr.remove("")
                for semestertemp in semester_list:

                    try:
                        dersname=lastmission[semestertemp][dersismi][0][0][code][0]
                        # if the try part works then we have the course in this sermester so we icrease it by one
                        semesterson=semesterson+1
                        # then we write  a x into the table
                        line.append("x")
                        line.append(",")
                        try:
                            # here we determine the right side of / in the last column
                            for prof in lastmission[semestertemp][dersismi][0][0][code][1]:
                                semesterinstr.add(prof)
                        except KeyError:
                            asdasdasdasd11111=9-8
                       # if the dirst try dowsnot work then we need a space in the table
                    except KeyError:
                        line.append(",")
                # we determined the dersname but we need it in 3 index
                line.insert(3,dersname)
                line.insert(4,",")
                line.append(str(semesterson)+"/")
                line.append(str(len(semesterinstr)))
                # finally we determine the lenght of semesterinstr and the value semesterson and add then into the list and we write then
                for l in line:
                    print(l,end="")
            if(not isinstance(code, int)):
                print()
