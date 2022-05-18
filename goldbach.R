library(schoolmath)

gb_list <- function(n) {
  i <- 1
  #empty vector
  list <- primes(2,n/2)
  
  while (list[i] <= n/2) {
    if (is.prim(n-list[i])) {
      # add elements to list  
      list <- append(list, sprintf("(%d, %d)  ", list[i], n-list[i]))
    }
    i <- i+1
  }
  return(list)
}

print_gb <- function(nmax) {
  for (j in seq(4,nmax,2)) {
    cat(sprintf("%d (%d partitions): ", j, length(gb_list(j))), gb_list(j), "\n")
  }
}

comb_count <- function(n) {
  i <- 1
  count <- 0
  
  while (i <= n/2) {
    if ((i> 1) && is.prim(i) && is.prim(n-i)) {
      count <- count + 1
    }
    i <- ifelse (n == 4, i+1, i+2)
  }
  return(count)
}

gb_partition_frame <- function(nmin, nmax) {
  x <- NULL
  y <- NULL
  frame <- NULL
  for (j in seq(nmin,nmax,2)) {
    x <- append(x,j)
    y <- append(y,comb_count(j))
    frame <- cbind(x,y)
  }
  return(frame)
}

gb_partition_plot <- function(nmax) {
  x <- NULL
  y <- NULL
  for (j in seq(4,nmax,2)) {
    x <- append(x,j)
    y <- append(y,comb_count(j))
  }
  plot(x,y, xlab = "even numbers", ylab = "numbers of partitions")
}

complete <- function(nmax) {
  print_gb(nmax)
  gb_partition_plot(nmax)
}

temp <- comb_count(4)