FROM debian:buster
RUN apt-get update && apt-get install -y gcc g++ make wget cmake doxygen
RUN apt-get install -y autoconf automake libtool bzip2
COPY --from=cxsc:latest /opt/lib/cxsc /opt/lib/cxsc
RUN cd /opt/lib && wget https://dl.bintray.com/boostorg/release/1.72.0/source/boost_1_72_0.tar.bz2 && tar xfj boost_1_72_0.tar.bz2 && ln -s boost_1_72_0 boost
ADD . /yalaa
RUN cd yalaa && autoreconf -i && ./configure --with-cxsc=/opt/lib/cxsc --with-boost=/opt/lib/boost --prefix=/opt/lib/yalaa && make && make install
