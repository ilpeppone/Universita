-- QUERY a
SELECT 
    AVG(p.peso) AS peso_medio,
    MAX(p.peso) AS peso_massimo,
    MIN(p.peso) AS peso_minimo,
    SUM(p.peso) AS peso_totale
FROM 
    PACCHETTI p
JOIN 
    UFFICI u ON p.Nufficio = u.nome
WHERE 
    u.citta = 'Milano';

-- QUERY b
SELECT 
    u.nome AS ufficio_postale,
    IFNULL(COUNT(p.id), 0) AS numero_pacchetti
FROM 
    UFFICI u
LEFT JOIN 
    PACCHETTI p ON u.nome = p.Nufficio
GROUP BY 
    u.nome;

-- QUERY c
SELECT
    c.codfisc AS codice_fiscale,
    c.nome AS nome_cliente,
    c.cognome AS cognome_cliente,
    p.tracking_number,
    p.peso,
    u.nome AS ufficio_postale,
    u.citta AS citta_ufficio,
    u.indirizzo AS indirizzo_ufficio
FROM
    CLIENTI c 
JOIN
    PACCHETTI p ON c.codfisc = p.cf_mittente
JOIN
    UFFICI u ON p.Nufficio = u.nome;
-- QUERY d
SELECT
    *
FROM
    IMPIEGATI
WHERE 
    data_inizio_lavoro BETWEEN '2021-01-01' AND '2021-10-01';
-- QUERY e
SELECT
    nome,
    IFNULL(COUNT(*), 0) -- ifnull non piace al prof
FROM 
    CLIENTI,PACCHETTI
WHERE
    codfisc=cf_mittente
GROUP BY
    cf_mittente
ORDER BY 
    COUNT(*) DESC
-- QUERY d