(ns compress
(:require [clojure.string :as str]))

(defn is_num [text] (not= (re-find #"^\d+?$" text) nil))
(defn space_after [text] (str/replace text #"[\[\(\-\@\$]" #(str %1 " ")))
(defn space_before [text] (str/replace text #"[\.\,\?\-\!\)\]]" #(str " " %1)))
(defn space [text] (space_before (space_after text)))
(defn get_words [text-file] (str/split (space (slurp text-file)) #"\s+"))
(defn start [index] (if (= index 0) "" " "))
(defn _compress [words]
  (let[ frequency-table (str/split  (str/lower-case (slurp "frequency.txt")) #"\s+")
    output (
    
      loop [i 0 out ""]
      (let 
        [word (if (not (nil? (get words i))) 
          (get words i)
          "")
        index (.indexOf frequency-table (str/lower-case  word))]

        (if (< i (count words))
            (recur
              (inc i)
              (if (= index -1)
                (if (is_num word)
                  (str out " @" word "@")
                  (str out (start i) word)
                )
                (str out (start i) index)
              )
            )
            out
            )
          )

      )
    ]
    output
  )
)
(defn compress_text [text-file]  (spit (str text-file ".ct") (_compress (get_words text-file))))


(defn rem_space_after [text] (str/replace text #"([\[\(\-\@\$]) " #(get %1 1)))
(defn rem_space_before [text] (str/replace text #" ([\.\,\?\-\!\)\]])" #(get %1 1)))
(defn rem_num [text] (str/replace text #"@(\d+)@" #(str (get %1 1) " ")))
(defn cap [text] (str/replace text #"\. (\w+)" #(str ". " (str/capitalize (get %1 1)))))
(defn cap1 [text] (str/replace text #"^ (\w+)" #(str/capitalize (get %1 1))))
(defn rem_re [text] (cap1 (cap (rem_num (rem_space_before (rem_space_after text))))))
(defn decompress_text [text-file]
  (let [file-contents (slurp text-file)
    words (str/split file-contents #"\s+")
    frequency-file (slurp "frequency.txt")
    frequency-table (str/split frequency-file #"\s+")
    output (
      loop [i 0 out ""]
        (if (< i (count words))
          (recur
            (inc i)
            (str out (loop [j 0] 
              (if ( = (get words i) (str j))
                (str " " (get frequency-table j))
                (if (< j (count frequency-table))
                  (recur
                    (inc j)
                  )
                  (str " " (get words i))
                )
              ))))
            out
          )
        )
    ]
    (rem_re output)
  )
)

