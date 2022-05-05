library(schoolmath)

gb_list <- function(x) {
  i <- 1
  #empty vector
  list <- NULL
  
  while (i <= x/2) {
    if ((i> 1) && is.prim(i) && is.prim(x-i)){
      # add elements to list  
      list <- append(list, sprintf("(%d, %d)  ", i, x-i))
    }
    i <- ifelse (x == 4, i+1, i+2)
  }
  return(list)
}

# input maximum number
nmax <- 1000

for (k in seq(4,nmax,2)) {
  cat(sprintf("%d: ", k), gb_list(k), "\n")
}