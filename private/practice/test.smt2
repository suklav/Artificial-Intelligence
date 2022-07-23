(set-option :produce-models true)
(set-logic QF_LIA)
(declare-fun x () Int)
(declare-fun y () Int)
(define-fun diff () Int (- x y))
(assert (= (+ x y) 9))
(assert (= (+ (* 2 x) (* 3 y)) 22))




(check-sat)
(get-model)
(exit)
