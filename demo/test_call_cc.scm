(display "test 1")
(display "test ##1")
(define xx #f)
(display "test ##2")
(display (+ 1 2 3
   (call/cc
    (lambda (ctx)
      (begin (set! xx ctx) 4)
      ))
   4 (+ 1 4)))

(display "test ##1")
#f
(display (xx 10))
(display (xx 11))
(display "test 2")
(define yy #f)

(display (+ (+ 1 2) 3
   (call/cc
    (lambda (ctx)
      (begin
        (set! yy ctx)
        (ctx 20)
        11)
      ))
   (+ 5 6)))
(display "test ##2")
(display (yy 10))
(display (yy 11))

(display "test 3")
(define aa #f)
(begin
  (display "start")
  (display
   (*
    (*
     (+ 1 2
        (call/cc
         (lambda (ctx)
           (begin
             (set! aa ctx)
             (display "in call/cc lambda")
             (ctx 3)
             2
             ))
         ) 4)
     2) 2)
   )
  (display "end")
  )
(display "test ##3")
(display "call aa")

(display (aa 1))

(define bb #f)
(display "test 4")
(define (func xx)
  (begin
    (display "enter func")
    (define yy (+ 1 2
       (call/cc
        (lambda (ctx)
          (begin
          (display "in call/cc proc")
          (set! bb ctx)
          (ctx 3)          
          2
          ))
        )
       4))
    (display "leave func")
    (+ yy xx)
    ))
(display "test ##4")
(display (func 1))
(display "test ##4")
(display (bb 4))
#f


(display "test 5")
(define (func5 x)
  (begin
    (display "enter func5")
    (display (call/cc
     (lambda (return)
       (+ 1 2 3 4
          (call/cc
           (lambda (return1)
             (begin
               (display "enter return1")
               (return1 10)
               (display "leave return1")
               (20))))
          5 x))))
    (display "leave func5")))

(func5 5)


(display "test 6")
(define (func6 x)
  (begin
    (display "enter func6")
    (display (call/cc
     (lambda (return)
       (+ 1 2 3 4
          (call/cc
           (lambda (return1)
             (begin
               (display "enter return1")
               (return 10)
               (display "leave return1")
               (20))))
          5 x))))
    (display "leave func6")))

(func6 5)
