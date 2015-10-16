

Country::Country(String name)
{
    this->name = name;
}

int Country::getTotalSoldiers()
{
    return soldiers;
}

String Country::getName()
{
    return name;
}

String Country::getOwner()
{
    return owners;
}

void Country::setOwner(String owner)
{
    this->owner = owner;
}

bool Country::addSoldiers(int amount)
{
    this->soldiers += amount;
}
