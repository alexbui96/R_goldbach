library(schoolmath)

gb_list <- function(n) {
  i <- 1
  #empty vector
  list <- NULL
  
  while (i <= n/2) {
    if ((i> 1) && is.prim(i) && is.prim(n-i)){
      # add elements to list  
      list <- append(list, sprintf("(%d, %d)  ", i, n-i))
    }
    i <- ifelse (n == 4, i+1, i+2)
  }
  return(list)
}

print_gb <- function(nmax) {
  for (j in seq(4,nmax,2)) {
    cat(sprintf("%d: ", j), gb_list(j), "\n")
  }
}

gb_partition <- function(nmax) {
  x <- NULL
  y <- NULL
  for (j in seq(4,nmax,2)) {
    x <- append(x,j)
    y <- append(y,length(gb_list(j)))
  }
  plot(x,y, xlab = "even number", ylab = "numbers of partitions")
}

complete <- function(nmax) {
  print_gb(nmax)
  gb_partition(nmax)
}

complete(1000)



