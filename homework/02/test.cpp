#ifndef __PROGTEST__

#include <cstring>
#include <cstdlib>
#include <cstdio>
#include <cctype>
#include <cmath>
#include <cassert>
#include <iostream>
#include <iomanip>
#include <string>
#include <vector>
#include <list>
#include <algorithm>
#include <memory>

using namespace std;
#endif /* __PROGTEST__ */

/**
 * Predeclaration for the links between
 */
class CCompRecord;

class CInvoiceRecord;

/**
 * Class for storing company record
 */
class CCompRecord{
    /**
     * Company and address identifier.
     * Variants *_lower identifiers are converted to lowercase. It helping prevent doing this each time when the comparing is needed.
     */
    string m_name;
    string m_addr;
    string m_name_lower;
    string m_addr_lower;

    /**
     * Company tax ID - external identifier
     */
    string m_taxID;

    /**
     * Simple storing sum of invoices because it is all needed from this relation between company and its invoices.
     * It could be changed into array of pointers to invoices (and accordingly calculate the result) in future if this won't be longer suitable.
     */
    unsigned sumInvoices;

public:
    /**
     * Constructor which creates new company.
     * @param name Company name
     * @param addr Company address
     * @param tax_id Company tas ID
     * @param sum_invoices Sum invoices in new company. Not mandatory, default value is 0.
     */
    CCompRecord(const string & name, const string & addr, const string & tax_id, unsigned int sum_invoices = 0)
            : m_name(name), m_addr(addr), m_taxID(tax_id), sumInvoices(sum_invoices){
        m_name_lower = name;
        m_addr_lower = addr;
        transform(m_name_lower.begin(), m_name_lower.end(), m_name_lower.begin(), ::tolower);
        transform(m_addr_lower.begin(), m_addr_lower.end(), m_addr_lower.begin(), ::tolower);
    }

    /**
     * Getters on class atributes. It allows to read and allow to prevent unwanted atributes changes.
     * Names of getters contain attributes names in its name, so they are selfdesribing.
     *
     * @return Reference to constant strings of these atributes
     */
    const string & getTaxID() const{
        return m_taxID;
    }

    const string & getName() const{return m_name;}

    const string & getAddr() const{return m_addr;}

    const string & getNameLower() const{return m_name_lower;}

    const string & getAddrLower() const{return m_addr_lower;}

    /**
     * Comparing method for sorting Companies by name and adress (aka NameID)
     * @param comp Reference to second Company which is on the right side of the comarision.
     * @return True if company from parameter is bigger, false otherwise
     */
    bool comByName(const CCompRecord & comp) const{
        if (m_name_lower < comp.getNameLower())
            return true;
        if (m_name_lower == comp.getNameLower() && m_addr_lower < comp.getAddrLower())
            return true;
        return false;
    }

    /**
     * Comparing methods for sorting Companies by its TaxID.
     * @param comp Reference to second Company which is on the right side of the comarision.
     * @return True if company from parameter is bigger, false otherwise
     */
    bool comByID(const CCompRecord & comp) const{
        return m_taxID < comp.getTaxID()? true : false;
    }

    /**
     * Getter to get company invoices summary.
     * @return Unsigned int of sum.
     */
    unsigned invCount() const{return sumInvoices;}

    /**
     * Setter to increase invoices summary.
     * @param price Amount of which should be add to invoices summary.
     */
    void invUpdate(unsigned price){sumInvoices += price;}
};

/**
 * Class for storing invoice records
 */
class CInvoiceRecord{
    /**
     * Simple attribute to store invoice amount.
     */
    unsigned amount;

public:
    /**
     * Constructor (explicit) creating new instance.
     * @param amount Amount of invoice.
     */
    explicit CInvoiceRecord(unsigned int amount) : amount(amount){}

    /**
     * Getter of invoice amount.
     * @return
     */
    unsigned getAmount() const{return amount;}

    /**
     * Method for comparing invoices.
     * @param inv Comparing invoice which is on the ride side of the compare.
     * @return true if the given invoice is bigger, false otherwise.
     */
    bool compare(const CInvoiceRecord & inv) const{return amount < inv.getAmount()? true : false;}
};

/**
 * Class for storing Companies and their Invoices
 */
class CVATRegister{
public:
    CVATRegister() = default;
    ~CVATRegister() = default;

    /**
     * Method creating new company identified by its name and address
     * @param name Company name
     * @param addr Company address
     * @param taxID Company taxID
     * @return true if company was created and stored, false if company with same Name+Adress or taxId is already listed.
     */
    bool newCompany(const string & name, const string & addr, const string & taxID);

    /**
     * Methot providing raw delete of given company from list
     * @param company shared ptr to deleting company
     * @return true if ok, false if error
     */
    bool deleteCompany(const shared_ptr<CCompRecord> & company);

    /**
     * Method deleting company from storage identified by its name and address.
     * @param name Company name
     * @param addr Company address
     * @return true if company was deleted, false if company not found
     */
    bool cancelCompany(const string & name, const string & addr);

    /**
     * Method deleting company from storage identified by its taxID.
     * @param taxID Company taxID identifier
     * @return true if company was deleted, false if company not found
     */
    bool cancelCompany(const string & taxID);

    /**
     * Method adding new invoice for company identified by its taxID
     * @param taxID Company taxID identifier
     * @param amount Amount of the invoice
     * @return true if invoice was listed, false if company not found
     */
    bool invoice(const string & taxID, unsigned int amount);

    /**
     * Method adding new invoice for company identified by its name and address.
     * @param taxID Company taxID identifier
     * @return true if invoice was listed, false if company not found
     */
    bool invoice(const string & name, const string & addr, unsigned amount);

    /**
     * Method counting invoices of one company identified by its name and address.
     * @param name Company name
     * @param addr Company address
     * @param sumIncome Input/output parameter for storing result
     * @return True if results was provided, false if company was not found.
     */
    bool audit(const string & name, const string & addr, unsigned & sumIncome) const;

    /**
     * Method counting invoices of one company identified by its taxID.
     * @param taxID Company taxID identifier
     * @param sumIncome Input/output parameter for storing result
     * @return True if results was provided, false if company was not found.
     */
    bool audit(const string & taxID, unsigned int & sumIncome) const;

    /**
     * Method providing name and address of the first company from list ordered alphabetically.
     * @param name Input/output parameter Company name
     * @param addr Input/output parameter Company address
     * @return true if processed correctly, false otherwise (empty list)
     */
    bool firstCompany(string & name, string & addr) const;

    /**
     * Method providing name and address of the next company from list ordered alphabetically.
     * @param name Input/output parameter Company name
     * @param addr Input/output parameter Company address
     * @return true if processed correctly, false otherwise (empty list)
     */
    bool nextCompany(string & name, string & addr) const;

    /**
     * Method returning median invoice. If there is even number of invoices, the bigger of the two middle invoices is used.
     * @return true if processed correctly, false otherwise (empty list)
     */
    unsigned int medianInvoice() const;
private:
    /**
     * Method for checking company data before input.
     * @param name Company name
     * @param addr Company address
     * @param taxID Company taxID identifier
     * @return true if data passed, false if there is some error
     */
    bool compValid(const string & name, const string & addr, const string & taxID) const;

    /**
     * Method searching company from storage identified by its name and address.
     * @param name Company name
     * @param addr Company address
     * @return Iterator in vector storage
     */
    bool findCompany(const string & name, const string & addr, shared_ptr<CCompRecord> & company) const;

    /**
     * Method searching company from storage identified by its taxID..
     * @param taxID Company taxID identifier
     * @return Iterator in vector storage
     */
    bool findCompany(const string & taxID, shared_ptr<CCompRecord> & company) const;

    /**
     * Method searching company by its taxID and adding amount to its sum.
     * @param taxID Company taxID identifier
     * @param amount Invoice amount
     * @return true if done, false otherwise (company not found)
     */
    bool addInvValue(const string & taxID, unsigned int amount);

    /**
     * Method searching company by its name and address and adding amount to its sum.
     * @param name Company name
     * @param addr Company address
     * @param amount Invoice amount
     * @return true if done, false otherwise (company not found)
     */
    bool addInvValue(const string & name, const string & addr, unsigned amount);

    /**
     * Vector field for storing companies ordered by Name-Adress
     */
    vector<shared_ptr<CCompRecord>> CompAlphaStorage;
    /**
     * Vector field for storing companies ordered by TaxID.
     */
    vector<shared_ptr<CCompRecord>> CompIDStorage;
    // This is not the best solution. I would prefer ordered SET of pointers (maybe again two or multiple keys).

    /**
     * Vector field for storing invoices. They are sorted each time the median is called (less probability of calling).
     */
    mutable vector<unique_ptr<CInvoiceRecord>> InvoiceStorage;

    /**
     * Index of the current company. It is used to read "current company" from list.
     */
    mutable size_t company_order = 0;
};

bool CVATRegister::compValid(const string & name, const string & addr, const string & taxID) const{
    if (name.empty() || addr.empty() || taxID.empty()) return false;
    return true;
}

bool CVATRegister::findCompany(const string & taxID, shared_ptr<CCompRecord> & company) const{
    auto query = make_shared<CCompRecord>(""s, " "s, taxID);
    auto item = lower_bound(CompIDStorage.begin(), CompIDStorage.end(), query,
                            [](const shared_ptr<CCompRecord> & c1, const shared_ptr<CCompRecord> & c2){
                                return c1->comByID(*c2);;
                            });


    if (item == CompIDStorage.end() || (*item)->getTaxID() != taxID)
        return false;
    company = (*item);
    return true;
}

bool CVATRegister::findCompany(const string & name, const string & addr, shared_ptr<CCompRecord> & company) const{
    auto query = make_shared<CCompRecord>(name, addr, " "s);
    auto item = lower_bound(CompAlphaStorage.begin(), CompAlphaStorage.end(), query,
                            [](const shared_ptr<CCompRecord> & c1, const shared_ptr<CCompRecord> & c2){
                                return c1->comByName(*c2);
                            });


    if (item == CompAlphaStorage.end() || (*item)->getNameLower() != query->getNameLower() ||
        (*item)->getAddrLower() != query->getAddrLower())
        return false;
    company = (*item);
    return true;
}

bool CVATRegister::addInvValue(const string & taxID, unsigned amount){
    shared_ptr<CCompRecord> company;
    if (!findCompany(taxID, company)) return false;
    company->invUpdate(amount);
    return true;
}

bool CVATRegister::addInvValue(const string & name, const string & addr, unsigned amount){
    shared_ptr<CCompRecord> company;
    if (!findCompany(name, addr, company)) return false;
    company->invUpdate(amount);
    return true;
}

bool CVATRegister::invoice(const string & taxID, unsigned amount){
    if (!addInvValue(taxID, amount)) return false;
    InvoiceStorage.emplace_back(make_unique<CInvoiceRecord>(amount));
    return true;
}

bool CVATRegister::invoice(const string & name, const string & addr, unsigned amount){
    if (!addInvValue(name, addr, amount)) return false;
    InvoiceStorage.emplace_back(make_unique<CInvoiceRecord>(amount));
    return true;
}

unsigned int CVATRegister::medianInvoice() const{
    if (InvoiceStorage.empty()) return 0;

    sort(InvoiceStorage.begin(), InvoiceStorage.end(),
         [](const unique_ptr<CInvoiceRecord> & i1, const unique_ptr<CInvoiceRecord> & i2){return i1->compare(*i2);});

    return InvoiceStorage[InvoiceStorage.size() / 2]->getAmount();
}

bool CVATRegister::audit(const string & name, const string & addr, unsigned int & sumIncome) const{
    shared_ptr<CCompRecord> company;
    if (!findCompany(name, addr, company)) return false;
    sumIncome = company->invCount();
    return true;
}

bool CVATRegister::audit(const string & taxID, unsigned int & sumIncome) const{
    shared_ptr<CCompRecord> company;
    if (!findCompany(taxID, company)) return false;
    sumIncome = company->invCount();
    return true;
}

bool CVATRegister::newCompany(const string & name, const string & addr, const string & taxID){
    //check valid input
    if (!compValid(name, addr, taxID)) return false;

    shared_ptr<CCompRecord> company;
    //check if company exists
    if (findCompany(taxID, company) || findCompany(name, addr, company)) return false;

    company = make_shared<CCompRecord>(name, addr, taxID);
    CompAlphaStorage.push_back(company);
    CompIDStorage.push_back(company);

    sort(CompAlphaStorage.begin(), CompAlphaStorage.end(),
         [](const shared_ptr<CCompRecord> & c1, const shared_ptr<CCompRecord> & c2){return c1->comByName(*c2);});
    sort(CompIDStorage.begin(), CompIDStorage.end(),
         [](const shared_ptr<CCompRecord> & c1, const shared_ptr<CCompRecord> & c2){return c1->comByID(*c2);});

    return true;
}

bool CVATRegister::deleteCompany(const shared_ptr<CCompRecord> & company){
    auto item = lower_bound(CompIDStorage.begin(), CompIDStorage.end(), company,
                            [](const shared_ptr<CCompRecord> & c1, const shared_ptr<CCompRecord> & c2){
                                return c1->comByID(*c2);;
                            });
    CompIDStorage.erase(item);

    item = lower_bound(CompAlphaStorage.begin(), CompAlphaStorage.end(), company,
                            [](const shared_ptr<CCompRecord> & c1, const shared_ptr<CCompRecord> & c2){
                                return c1->comByName(*c2);
                            });

    CompAlphaStorage.erase(item);

    return true;

}

bool CVATRegister::cancelCompany(const string & name, const string & addr){
    shared_ptr<CCompRecord> company;
    if (!findCompany(name, addr, company)) return false;

    deleteCompany(company);
    return true;
}

bool CVATRegister::cancelCompany(const string & taxID){
    shared_ptr<CCompRecord> company;
    if (!findCompany(taxID, company)) return false;

    deleteCompany(company);
    return true;
}

bool CVATRegister::firstCompany(string & name, string & addr) const{
    company_order = 0;
    if (CompAlphaStorage.empty()) return false;
    name = CompAlphaStorage[company_order]->getName();
    addr = CompAlphaStorage[company_order]->getAddr();
    return true;
}

bool CVATRegister::nextCompany(string & name, string & addr) const{
    if (company_order + 1 >= CompAlphaStorage.size()) return false;
    ++company_order;
    name = CompAlphaStorage[company_order]->getName();
    addr = CompAlphaStorage[company_order]->getAddr();
    return true;
}


#ifndef __PROGTEST__

int main(void){
    string name, addr;
    unsigned int sumIncome;

    CVATRegister b1;
    assert (b1.newCompany("ACME", "Thakurova", "666/666"));
    assert (b1.newCompany("ACME", "Kolejni", "666/666/666"));
    assert (b1.newCompany("Dummy", "Thakurova", "123456"));
    assert (b1.invoice("666/666", 2000));
    assert (b1.medianInvoice() == 2000);
    assert (b1.invoice("666/666/666", 3000));
    assert (b1.medianInvoice() == 3000);
    assert (b1.invoice("123456", 4000));
    assert (b1.medianInvoice() == 3000);
    assert (b1.invoice("aCmE", "Kolejni", 5000));
    assert (b1.medianInvoice() == 4000);
    assert (b1.audit("ACME", "Kolejni", sumIncome) && sumIncome == 8000);
    assert (b1.audit("123456", sumIncome) && sumIncome == 4000);
    assert (b1.firstCompany(name, addr) && name == "ACME" && addr == "Kolejni");
    assert (b1.nextCompany(name, addr) && name == "ACME" && addr == "Thakurova");
    assert (b1.nextCompany(name, addr) && name == "Dummy" && addr == "Thakurova");
    assert (!b1.nextCompany(name, addr));
    assert (b1.cancelCompany("ACME", "KoLeJnI"));
    assert (b1.medianInvoice() == 4000);
    assert (b1.cancelCompany("666/666"));
    assert (b1.medianInvoice() == 4000);
    assert (b1.invoice("123456", 100));
    assert (b1.medianInvoice() == 3000);
    assert (b1.invoice("123456", 300));
    assert (b1.medianInvoice() == 3000);
    assert (b1.invoice("123456", 200));
    assert (b1.medianInvoice() == 2000);
    assert (b1.invoice("123456", 230));
    assert (b1.medianInvoice() == 2000);
    assert (b1.invoice("123456", 830));
    assert (b1.medianInvoice() == 830);
    assert (b1.invoice("123456", 1830));
    assert (b1.medianInvoice() == 1830);
    assert (b1.invoice("123456", 2830));
    assert (b1.medianInvoice() == 1830);
    assert (b1.invoice("123456", 2830));
    assert (b1.medianInvoice() == 2000);
    assert (b1.invoice("123456", 3200));
    assert (b1.medianInvoice() == 2000);
    assert (b1.firstCompany(name, addr) && name == "Dummy" && addr == "Thakurova");
    assert (!b1.nextCompany(name, addr));
    assert (b1.cancelCompany("123456"));
    assert (!b1.firstCompany(name, addr));

    CVATRegister b2;
    assert (b2.newCompany("ACME", "Kolejni", "abcdef"));
    assert (b2.newCompany("Dummy", "Kolejni", "123456"));
    assert (!b2.newCompany("AcMe", "kOlEjNi", "1234"));
    assert (b2.newCompany("Dummy", "Thakurova", "ABCDEF"));
    assert (b2.medianInvoice() == 0);
    assert (b2.invoice("ABCDEF", 1000));
    assert (b2.medianInvoice() == 1000);
    assert (b2.invoice("abcdef", 2000));
    assert (b2.medianInvoice() == 2000);
    assert (b2.invoice("aCMe", "kOlEjNi", 3000));
    assert (b2.medianInvoice() == 2000);
    assert (!b2.invoice("1234567", 100));
    assert (!b2.invoice("ACE", "Kolejni", 100));
    assert (!b2.invoice("ACME", "Thakurova", 100));
    assert (!b2.audit("1234567", sumIncome));
    assert (!b2.audit("ACE", "Kolejni", sumIncome));
    assert (!b2.audit("ACME", "Thakurova", sumIncome));
    assert (!b2.cancelCompany("1234567"));
    assert (!b2.cancelCompany("ACE", "Kolejni"));
    assert (!b2.cancelCompany("ACME", "Thakurova"));
    assert (b2.cancelCompany("abcdef"));
    assert (b2.medianInvoice() == 2000);
    assert (!b2.cancelCompany("abcdef"));
    assert (b2.newCompany("ACME", "Kolejni", "abcdef"));
    assert (b2.cancelCompany("ACME", "Kolejni"));
    assert (!b2.cancelCompany("ACME", "Kolejni"));

    CVATRegister b3;
    assert (b3.newCompany("ACME", "Kolejni", "abcdef"));
    assert (!b3.newCompany("aCME", "Kolejni", "123456"));
    assert (b3.newCompany("aCME", "Strahov", "123456"));
    assert (b3.newCompany("aCME  fsdf", "Strahov  fdsf", "123456789"));
    assert (!b3.newCompany("aCmE", "Most", "123456"));
    assert (b3.newCompany("aCmE", "Most", "sdf35g4dsfgdfgdfg*df/gdfgdf"));
    assert (b3.newCompany("aCme", "As", "sdf35g4dsfgdfgdfg"));
    assert (b3.cancelCompany("acme", "most"));
    assert (b3.newCompany(
            "HHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHH",
            "HHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHH", "Tnbhyatnledcca"));
    assert (b3.newCompany(
            "HHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHH",
            "HHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHH", "Tnbhyatnledcc"));


    CVATRegister b4;
    assert(b4.newCompany("abCs", "Praha", "123456"));
    assert(!b4.cancelCompany("12345"));
    assert(!b4.cancelCompany("", ""));
    assert(b4.newCompany("abc", "def", "abcdef1"));
    assert(b4.newCompany("ab", "cdef", "abcdef2"));


    return EXIT_SUCCESS;
}

#endif /* __PROGTEST__ */
