#lang scheme
;2016400324

(define (firstcase farmname FARMS)(cond ((eqv? (length FARMS) 0)' 0)((equal? farmname (caar FARMS))(cadar FARMS)) (else (firstcase farmname (cdr FARMS)))))
(define (TRANSPORTATION-COST farmname) (firstcase farmname FARMS))


(define (secondcase farmname FARMS)(cond ((eqv? (length FARMS) 0)'())((equal? farmname (caar FARMS))(caddar FARMS)) (else (secondcase farmname (cdr FARMS)))))
(define (AVAILABLE-CROPS farmname) (secondcase farmname FARMS))



(define (thirdcase personname CUSTOMERS)(cond ((eqv? (length CUSTOMERS) 0)'()) ( (equal? personname (caar CUSTOMERS)) (caddar CUSTOMERS) ) (else (thirdcase personname (cdr CUSTOMERS)))))
(define (INTERESTED-CROPS personname) (thirdcase personname CUSTOMERS))


(define (forthcase personname CUSTOMERS)(cond ((eqv? (length CUSTOMERS) 0)'())((equal? personname (caar CUSTOMERS))(cadar CUSTOMERS)) (else (forthcase personname (cdr CUSTOMERS)))))
(define (CONTRACT-FARMS personname) (forthcase personname CUSTOMERS))


(define (member? x list)
     (if (null? list) #f                                
         (if (equal? x (car list)) #t                   
              (member? x (cdr list)))))    

(define (fifthcase farmnamex listtoreturn CUSTOMERS)(cond
 ((eqv? (length CUSTOMERS) 0) listtoreturn)
((member? farmnamex (cadar CUSTOMERS)) (fifthcase farmnamex (append listtoreturn (list (caar CUSTOMERS)) ) (cdr CUSTOMERS)))
 (else (fifthcase farmnamex listtoreturn (cdr CUSTOMERS)))))
(define (CONTRACT-WITH-FARM farmnamex) (fifthcase farmnamex '() CUSTOMERS))


(define (sixthcase meyveismi listtoreturn CUSTOMERS)(cond
 ((eqv? (length CUSTOMERS) 0) listtoreturn)
((member? meyveismi (caddar CUSTOMERS)) (sixthcase meyveismi (append  listtoreturn (list (caar CUSTOMERS))) (cdr CUSTOMERS)))
 (else (sixthcase meyveismi listtoreturn (cdr CUSTOMERS)))))
(define (INTERESTED-IN-CROP meyveismi) (sixthcase meyveismi '() CUSTOMERS))


(define (find meyve CROPS) (cond ((eqv? (length CROPS) 0) 0) ((equal? meyve (caar CROPS)) (caddar CROPS)) (else (find meyve (cdr CROPS)))))

(define (seventhcase meyveismix minnumber CROPS)(cond ((eqv? (length CROPS) 0) minnumber)((and (equal? meyveismix (caar CROPS))(> minnumber (caddar CROPS)))(seventhcase meyveismix (caddar CROPS) (cdr CROPS))) (else (seventhcase meyveismix minnumber (cdr CROPS)))))
(define (MIN-SALE-PRICE meyveismix) (seventhcase meyveismix (find meyveismix CROPS) CROPS))


(define (eightthcase interval1 interval2 listtoreturn CROPS)(cond
 ((eqv? (length CROPS) 0) listtoreturn)
((and (<= (caddar CROPS) interval2) (>= (caddar CROPS) interval1)) (eightthcase interval1 interval2 (append  listtoreturn (list (caar CROPS))) (cdr CROPS)))
 (else (eightthcase interval1 interval2 listtoreturn (cdr CROPS)))))
(define (CROPS-BETWEEN interval1 interval2) (eightthcase interval1 interval2 '() CROPS))


(define (farmtorise meyve  listtoreturn FARMS) (cond ((eqv? (length FARMS) 0) listtoreturn) ((member? meyve (caddar FARMS))(farmtorise meyve  (append listtoreturn (list(caar FARMS))) (cdr FARMS)) )
  (else (farmtorise meyve  listtoreturn (cdr FARMS)))

  )

)

(define intersect
  (lambda (set1 set2)
    (cond
      ((null? set1)(quote ()))
      ((member (car set1) set2)
       (cons (car set1)
             (intersect (cdr set1) set2)))
      (else (intersect (cdr set1) set2)))))


(define (findfarmandmeyve meyve farmname CROPS) (cond ((eqv? (length CROPS) 0) 90) ((and (equal? meyve (caar CROPS)) (equal? farmname (cadar CROPS))) (caddar CROPS))
(else (findfarmandmeyve meyve farmname (cdr CROPS)))))


(define (ninethcase meyve numbertoreturn insccontractedfarmers) (cond ( (eqv? (length insccontractedfarmers) 0) numbertoreturn)
((> numbertoreturn (+(TRANSPORTATION-COST (car insccontractedfarmers))(findfarmandmeyve meyve (car insccontractedfarmers) CROPS)))
 (ninethcase meyve (+(TRANSPORTATION-COST (car insccontractedfarmers))(findfarmandmeyve meyve (car insccontractedfarmers) CROPS)) (cdr insccontractedfarmers ) ))
      (else (ninethcase meyve numbertoreturn (cdr insccontractedfarmers )) )                                                                ))
(define (BUY-PRICE personname meyveismi) (ninethcase  meyveismi 999999999 (intersect (CONTRACT-FARMS personname) (farmtorise meyveismi '() FARMS))))



(define (tenthcase personname returnvalue meyvelist) ( cond ((eqv? (length meyvelist) 0) returnvalue) (else (tenthcase personname (+ returnvalue (BUY-PRICE personname (car meyvelist))) (cdr meyvelist)))))
(define (TOTAL-PRICE personname) (tenthcase personname 0 (INTERESTED-CROPS personname)))

