#lang racket

(require rackunit "grocery_solution.rkt")

(equal? (TRANSPORTATION-COST 'farmA) 100)
(equal? (TRANSPORTATION-COST 'farmB) 90)
(equal? (TRANSPORTATION-COST 'farmC) 75)
(equal? (TRANSPORTATION-COST 'farmD) 75)
(equal? (TRANSPORTATION-COST 'farm_not_in_database) 0)

(equal? (AVAILABLE-CROPS 'farmA) (list 'apricot 'apple 'blueberry))
(equal?(AVAILABLE-CROPS 'farmD) empty)
(equal? (AVAILABLE-CROPS 'farm_not_in_database) empty)

(equal? (INTERESTED-CROPS 'john) (list 'apricot 'lemon))
(equal? (INTERESTED-CROPS 'elenor) empty)
(equal? (INTERESTED-CROPS 'customer_not_in_database) empty)

(equal? (CONTRACT-FARMS 'john) (list 'farmA 'farmC))
(equal? (CONTRACT-FARMS 'elenor) empty)
(equal? (CONTRACT-FARMS 'customer_not_in_database) empty)

(equal? (CONTRACT-WITH-FARM 'farmA) (list 'john))
(equal? (CONTRACT-WITH-FARM 'farmB) (list 'james 'arya))
(equal? (CONTRACT-WITH-FARM 'farmC) (list 'john 'james))
(equal? (CONTRACT-WITH-FARM 'farmD) (list 'arya))
(equal? (CONTRACT-WITH-FARM 'farm_not_in_database) empty)

(equal? (INTERESTED-IN-CROP 'apricot) (list 'john))
(equal? (INTERESTED-IN-CROP 'grape) (list 'james 'arya))
(equal? (INTERESTED-IN-CROP 'lemon) (list 'john))
(equal? (INTERESTED-IN-CROP 'corn) (list 'james))
(equal? (INTERESTED-IN-CROP 'broccoli) (list 'arya))
(equal? (INTERESTED-IN-CROP 'crop_not_in_database) empty)

(equal? (MIN-SALE-PRICE 'apricot) 10)
(equal? (MIN-SALE-PRICE 'apple) 12)
(equal? (MIN-SALE-PRICE 'blueberry) 15)
(equal? (MIN-SALE-PRICE 'broccoli) 8)
(equal? (MIN-SALE-PRICE 'carrot) 5)
(equal? (MIN-SALE-PRICE 'grape) 10)
(equal? (MIN-SALE-PRICE 'corn) 9)
(equal? (MIN-SALE-PRICE 'lemon) 10)
(equal? (MIN-SALE-PRICE 'crop_not_in_database) 0)

(equal? (CROPS-BETWEEN 11 15) (list 'apple 'blueberry 'grape))
(equal? (CROPS-BETWEEN 7 10) (list 'apricot 'broccoli 'grape 'corn 'lemon))
(equal? (CROPS-BETWEEN 100 200) '())

(equal? (BUY-PRICE 'john 'apricot) 110)
(equal? (BUY-PRICE 'john 'lemon) 85)
(equal? (BUY-PRICE 'james 'corn) 84)
(equal? (BUY-PRICE 'james 'grape) 87)
(equal? (BUY-PRICE 'arya 'grape) 100)
(equal? (BUY-PRICE 'arya 'broccoli) 98)

(equal? (TOTAL-PRICE 'john) 195)
(equal? (TOTAL-PRICE 'james) 171)
(equal? (TOTAL-PRICE 'arya) 198)
(equal? (TOTAL-PRICE 'elenor) 0)
(equal? (TOTAL-PRICE 'customer_not_in_database) 0)
