DIA=dia
DIA_EPS_FLAGS=--filter=eps-pango
DIA_EXPORT_FLAGS=--export=
EPSTOPDF=epstopdf

PICS := $(patsubst %.dia,%.pdf,$(wildcard *.dia))

all: $(PICS)

%.eps: %.dia
	$(DIA) $(DIA_EPS_FLAGS) $(DIA_EXPORT_FLAGS)$@ $<

%.pdf: %.eps
	 epstopdf $<

clean:
	rm -f *.pdf
	rm -f *.eps
