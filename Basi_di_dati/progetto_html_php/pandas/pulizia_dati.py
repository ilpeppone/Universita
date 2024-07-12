import pandas as pd

#importiamo il CSV senza indicizzare perché potrebbero esserci duplicati
# tra tutti gli attributi, che verranno eventualmente rimossi con il metodo drop_duplicates
df_artisti = pd.read_csv("/home/peppe/Progetto_base_dati/pandas/artist_data.csv")

#conversione delle colonne nell'ordine corretto, riempimento dei valori mancanti e nel tipo di dato appropriato 
df_artisti['id'] = pd.to_numeric(df_artisti['id'], errors='coerce').astype(pd.Int32Dtype()) 
df_artisti['name'] = df_artisti['name'].astype(str)
df_artisti['gender'] = df_artisti['gender'].astype(str)
df_artisti=df_artisti.drop(columns=['dates'])#dates tolte perchè derivate
df_artisti['yearOfBirth'] = pd.to_numeric(df_artisti['yearOfBirth'], errors='coerce').astype(pd.Int32Dtype()) 
df_artisti['yearOfDeath'] = pd.to_numeric(df_artisti['yearOfDeath'], errors='coerce').astype(pd.Int32Dtype())
df_artisti['placeOfBirth'] = df_artisti['placeOfBirth'].astype(str)
df_artisti['placeOfDeath'] = df_artisti['placeOfDeath'].astype(str)
df_artisti['url'] = df_artisti['url'].astype(str)

print(df_artisti.dtypes)#verifichiamo se interpretati i dati nel dataframe come ci aspettiamo
print(df_artisti.shape)#verifichiamo quante tuple e attributi ci sono

df_artisti = df_artisti.drop_duplicates()# rimuoviamo eventuali ridondaze fra tuple

print(df_artisti.shape)#verifichiamo quante tuple e attributi ci sono dopo aver eliminato duplicati
max_lengths = df_artisti.apply(lambda col: col.astype(str).str.len().max())
print(max_lengths)#verifico la dimensione massima di ogni colonna degli artisti per stringa
df_artisti.to_csv('/home/peppe/Progetto_base_dati/artisti_puliti.csv', index=False, na_rep='NULL')#esportiamo senza indicizzare
#con na_rep='NULL' riempiamo tutti i valori VUOTI (pd.NA) con NULL come ad esempio le date
#le stringhe invece vengo automaticamente riempite con nan se ci sono valori vuoti
#########

# creiamo il dataframe df_lavori importando il CSV artwork_data
df_lavori = pd.read_csv("/home/peppe/Progetto_base_dati/pandas/artwork_data.csv")

#conversione delle colonne nell'ordine corretto, riempimento dei valori mancanti e nel tipo di dato appropriato 
df_lavori['id'] = pd.to_numeric(df_lavori['id'],  errors='coerce').astype(pd.Int32Dtype())
df_lavori['accession_number'] = df_lavori['accession_number'].astype(str)
df_lavori= df_lavori.drop(columns=['artist'])#artist lo tolgo perchè il nome è già presente nel csv degli artisti
df_lavori['artistRole'] = df_lavori['artistRole'].astype(str)
df_lavori['artistId'] = pd.to_numeric(df_lavori['artistId'],  errors='coerce').astype(pd.Int32Dtype())
df_lavori['title'] = df_lavori['title'].astype(str)
df_lavori['dateText'] = df_lavori['dateText'].astype(str)#lo lascio perchè ci sono informazioni aggiuntive
df_lavori['medium'] = df_lavori['medium'].astype(str)
df_lavori['creditLine'] = df_lavori['creditLine'].astype(str)
df_lavori['year'] = pd.to_numeric(df_lavori['year'], errors='coerce').astype(pd.Int32Dtype())
df_lavori['acquisitionYear'] = pd.to_numeric(df_lavori['acquisitionYear'], errors='coerce').astype(pd.Int32Dtype())
df_lavori['dimensions'] = df_lavori['dimensions'].astype(str)
df_lavori = df_lavori.drop(columns=['width', 'height', 'depth','units'])#width,height,depth sono derivati da dimensions
#units lo tolgo perchè già presente nel csv degli artisti
df_lavori['inscription'] = df_lavori['inscription'].astype(str)
df_lavori['thumbnailCopyright'] = df_lavori['thumbnailCopyright'].astype(str)
df_lavori['thumbnailUrl'] = df_lavori['thumbnailUrl'].astype(str)
df_lavori['url'] = df_lavori['url'].astype(str)

print(df_lavori.dtypes)#visualizziamo se i dati sono stati convertiti nel tipo che abbiamo indicato

print(df_lavori.shape)#verifichiamo quanti valori ci sono
df_artisti=df_lavori.drop_duplicates() #eliminazione di eventuali righe duplicate
print(df_lavori.shape)#verifichiamo quanti valori ci sono dopo aver eliminato i duplicati
# Calcola la lunghezza massima dei valori in ciascuna colonna
max_lengths = df_lavori.apply(lambda col: col.astype(str).str.len().max())
#verifico la dimensione massima di ogni colonna delle opere per stringa
print(max_lengths)
df_lavori.to_csv('/home/peppe/Progetto_base_dati/lavori_puliti.csv', index=False, na_rep='NULL')#esportiamo senza indicizzare
#con na_rep='NULL' riempiamo tutti i valori VUOTI (pd.NA) con NULL come ad esempio le date
#le stringhe invece vengo automaticamente riempite con nan se ci sono valori vuoti
