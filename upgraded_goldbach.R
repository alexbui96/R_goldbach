library(schoolmath)

stacked_primes_list <- function(n) {
  max <- sqrt(n)
  stacked_prime <- 2
  i <- 1
  while ((2*i +1) < max){
    if(is.prim(2*i + 1)) {
      stacked_prime <- append(stacked_prime, (2*i + 1))
    }
    i <- i + 1
  }
  return(stacked_prime)
}

goldbach_list <- function(n) {
  i <- 1
  prime_list <- primes(2,n/2)
  list <- NULL
  
  while (i < length(prime_list)) {
    if (is.prim(n - prime_list[i])) {
      # add elements to list  
      list <- append(list, sprintf("(%d, %d)", prime_list[i], n - prime_list[i]))
    }
    i <- i+1
  }
  return(list)
}

goldbach_count <- function(n) {
  i <- 1
  prime_list <- primes(2,n/2)
  list <- NULL
  count <- 0
  
  while (i < length(prime_list)) {
    if (is.prim(n - prime_list[i])) {
      count <- count + 1
    }
    i <- i+1
  }
  return(count)
}

check_goldbach <- function(n) {
  i <- 1
  prime_list <- primes(2,n/2)
  list <- NULL
  
  while (i < length(prime_list)) {
    if (is.prim(n - prime_list[i])) {
     return(c(prime_list[i], n - prime_list[i]))
    }
    i <- i+1
  }
}

goldbach_partition_plot <- function(nmax) {
  x <- NULL
  y <- NULL
  for (j in seq(4,nmax,2)) {
    x <- append(x,j)
    y <- append(y,goldbach_count(j))
  }
  plot(x,y, xlab = "even numbers", ylab = "numbers of partitions")
}

goldbach_partition_plot(1000)
