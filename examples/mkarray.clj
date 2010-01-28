(defn add-hash-entry [hash pair]
  (conj { (first pair) (second pair) } hash))


(prn
(reduce 
  add-hash-entry
  {}
  (map vector '(:a :b :c) '(1 2 3)))
)

  ;(fn [result pair]  (conj {pair.first pair.second} result))
  ;(fn [result pair] (conj {(first pair) (second pair)} result))
