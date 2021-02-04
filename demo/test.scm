(define (func x y)
  (begin
    (define z 10)
    (define u 20)
    (display (env))
    (display z)
    (display u)
    (lambda () (+ x y z u))))


((func 10 10))
