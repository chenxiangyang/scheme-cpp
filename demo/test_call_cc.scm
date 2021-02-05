
(define xx #f)
(+ 1 2 3
   (call/cc
    (lambda (ctx)
      (begin (set! xx ctx) 4)
      ))
   4 (+ 1 4))

#f
(display (xx 10))
(display (xx 11))

(define yy #f)

(+ (+ 1 2) 3
   (call/cc
    (lambda (ctx)
      (begin
        (set! yy ctx)
        (display (ctx 20))
        11)
      ))
   (+ 5 6))


(display "aaaaaaa")
(display (yy 10))
(display "bbbbbbb")
(display (yy 11))
(display "ccccccc")


(define aa #f)
(begin
  (display
   (*
    (*
     (+ 1 2
        (call/cc
         (lambda (ctx)
           (begin
             (set! aa ctx)
             (display "in call/cc lambda")
             (ctx 10)
             10
             ))
         ) 4)
     2) 2)
   )
  (display "end\n")
  (display "end2\n")
  )


#f
