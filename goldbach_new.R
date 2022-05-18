goldbach_list <- function(n) {
  i <- 1
  primes_list <- generate_primes(2, n)
  list <- NULL
  while (primes_list[i] <= n/2) {
    if ((n-primes_list[i]) %in% primes_list) {
      list <- append(list, sprintf("(%d, %d)  ", primes_list[i], n - primes_list[i]))
    }
    i <- i+1
  }
  return(list)
}

goldbach_partition_count <- function(n) {
  i <- 1
  count <- 0
  primes_list <- generate_primes(2, n)
  list <- NULL
  while (primes_list[i] <= n/2) {
    if ((n-primes_list[i]) %in% primes_list) {
      count <- count + 1
    }
    i <- i+1
  }
  return(count)
}

goldbach_partition_frame <- function(nmin,nmax) {
  x <- NULL
  y <- NULL
  frame <- NULL
  primes_list <- generate_primes(2, nmax)
  count <- 0
  for (i in seq(nmin,nmax,2)) {
    x <- append(x,i)
    j <- 1
    while (primes_list[j] <= i/2) {
      if ((i-primes_list[j]) %in% primes_list) {
        count <- count + 1
      }
      j <- j + 1
    }
    y <- append(y,count)
    count <- 0
    frame <- as.data.frame(cbind(x,y))
  }
  plot(frame, xlab = "Even Numbers", ylab = "Number of Partitions")
  return(frame)
}