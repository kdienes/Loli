(require 'loli-package "package")
(require 'loli-obj "loli-obj")
(require 'loli-prim "loli-prim")
(require 'loli-type-class "loli-typeclass")
(require 'loli-env "loli-env")
(require 'loli-read "loli-read")
(require 'loli-error "loli-error")

(in-package #:loli)

(defun loli-get-new-value ()
  (format *standard-output* "New Value: ")
  (multiple-value-list (loli-read-from-string (loli-get-input *query-io*))))

(defun loli-symbol-not-bound-debug (obj env)
  (do ()
      ((or
        (not (equal loli-nil (loli-lookup obj env)))
        (equal (loli-obj-value obj) 't)
        (equal (loli-obj-value obj) 'nil)))
    (restart-case
        (cerror "Symbol not bound" 'loli-err-symbol-not-bound :err-obj obj :err-env env)
      (use-new-value (new-value)
        :report "Enter a new value"
        :interactive (lambda ()
                       (format *query-io* "New Value: ")
                       (force-output *query-io*)
                       (list (loli-read-from-string (loli-get-input *query-io*))))
        (setq obj new-value))))
  (loli-simple-eval obj env))

(defun handle-loli-symbol-not-bound (condition)
  (when (typep condition 'loli-err-symbol-not-bound)
    (loli-symbol-not-bound-debug (err-obj condition) (err-env condition))))

(defun loli-eval-sym (sym &optional (env *TOP-ENV*))
  (handler-bind ((loli-err-symbol-not-bound #'handle-loli-symbol-not-bound))
    (cond
      ((equalp (loli-obj-value sym) 'nil)
       (return-from loli-eval-sym loli-nil))
      ((equalp (loli-obj-value sym) 't)
       (return-from loli-eval-sym loli-t))
      ((and (null env) (null (loli-obj-env sym)))
       (loli-symbol-not-bound-debug sym env))
      ((not (null (loli-obj-env sym)))
       (let ((r (loli-lookup sym (loli-obj-env sym))))
         (if (not (equal r loli-nil))
             (return-from loli-eval-sym r)
             (loli-symbol-not-bound-debug sym env))))
      ((not (null env))
       (let ((r (loli-lookup sym env)))
         (if (not (equal r loli-nil))
             (return-from loli-eval-sym r)
             (loli-symbol-not-bound-debug sym env))))
      (t
       (loli-symbol-not-bound-debug sym env)))))

(defun loli-eval-cons (lcons &optional (env '()))
  )

(defun loli-simple-eval (obj &optional (env *TOP-ENV*))
  (cond
    ((sub-type-p (loli-obj-loli-type obj)
                 *type-sym*)
     (loli-eval-sym obj env))
    ((sub-type-p (loli-obj-loli-type obj)
                 *type-cons*)
     (loli-eval-cons obj env))
    (t obj)))

(defun loli-output (obj &optional (output-stream *standard-output*))
  (cond
    ((sub-type-p (loli-obj-loli-type obj)
                 *type-fn*)
     (cond
       ((sub-type-p (loli-obj-loli-type obj)
                    *type-proc*)
        (format output-stream "<Primitive Procedure ~{~A~^,~} => ~A>"
                (make-list
                 (loli-proc-struct-arity (loli-obj-value obj))
                 :initial-element
                 (loli-type-class-id
                  (loli-proc-struct-arg-type (loli-obj-value obj))))
                (loli-type-class-id
                 (loli-proc-struct-return-type (loli-obj-value obj)))))
       ((sub-type-p (loli-obj-loli-type obj)
                    *type-lambda*)
        (format output-stream "<Lambda Expression ~{~A~^,~} => ~A>"
                (loop for a in (loli-lambda-struct-arg-types (loli-obj-value obj))
                   collect (loli-type-class-id a))
                (loli-type-class-id
                 (loli-lambda-struct-return-type (loli-obj-value obj)))))
       (t
        (format output-stream "<Unknown Function>"))))
    ((sub-type-p (loli-obj-loli-type obj)
                 *type-cons*)
     (format output-stream "(")
     (loli-output (loli-head obj) output-stream)
     (if (sub-type-p (loli-obj-loli-type (loli-tail obj))
                     *type-cons*)
         (progn
           (format output-stream " ")
           (loli-output (loli-tail obj) output-stream)
           (format output-stream ")"))
         (progn
           (format output-stream " . ")
           (loli-output (loli-tail obj) output-stream)
           (format output-stream ")"))))
    (t
     (format output-stream "~A" (loli-obj-value obj)))))


(defun loli-rep (&optional (in-stream *standard-input*) (env *TOP-ENV*) (out-stream *standard-output*))
  (let ((i (loli-get-input in-stream)))
    (if (equalp i "")
        nil
        (let ((o (loli-simple-eval (loli-read-from-string i env) env)))
          (loli-output o out-stream)))))

(provide 'loli-repl)
