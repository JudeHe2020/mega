#include "UpsellPlans.h"

// ************************************************************************************************
// * UpsellPlans
// ************************************************************************************************

UpsellPlans::UpsellPlans(QObject* parent):
    QObject(parent),
    mViewMode(ViewMode::NONE),
    mIsMonthly(true),
    mIsBillingCurrency(true),
    mCurrentDiscount(-1),
    mTransferFinishTime(0ll),
    mIsOnlyProFlexiAvailable(false),
    mIsPro(false),
    mIsAnyPlanClicked(false)
{}

void UpsellPlans::addPlans(const QList<std::shared_ptr<Data>>& plans)
{
    if (plans.isEmpty())
    {
        return;
    }

    mPlans.append(plans);
    emit sizeChanged();
}

std::shared_ptr<UpsellPlans::Data> UpsellPlans::getPlan(int index) const
{
    if (index < 0 || index >= mPlans.size())
    {
        return nullptr;
    }

    return mPlans.at(index);
}

int UpsellPlans::size() const
{
    return mPlans.size();
}

UpsellPlans::ViewMode UpsellPlans::getViewMode() const
{
    return mViewMode;
}

QString UpsellPlans::getCurrencySymbol() const
{
    return mCurrency.currencySymbol();
}

QString UpsellPlans::getCurrencyName() const
{
    return mCurrency.currencyName();
}

QString UpsellPlans::getTransferRemainingTime() const
{
    return mTransferRemainingTime;
}

void UpsellPlans::setCurrency(const QString& symbol, const QString& name)
{
    mCurrency.setCurrencySymbol(symbol);
    mCurrency.setCurrencyName(name);
    emit currencyChanged();
}

void UpsellPlans::setTransferFinishTime(long long newTime)
{
    mTransferFinishTime = newTime;
}

void UpsellPlans::setOnlyProFlexiAvailable(bool onlyProFlexiAvailable)
{
    if (mIsOnlyProFlexiAvailable != onlyProFlexiAvailable)
    {
        mIsOnlyProFlexiAvailable = onlyProFlexiAvailable;
        emit onlyProFlexiAvailableChanged();
    }
}

void UpsellPlans::setPro(bool isPro)
{
    if (mIsPro != isPro)
    {
        mIsPro = isPro;
        emit isProChanged();
    }
}

void UpsellPlans::setIsAnyPlanClicked(bool isAnyPlanClicked)
{
    mIsAnyPlanClicked = isAnyPlanClicked;
}

bool UpsellPlans::isAnyPlanClicked() const
{
    return mIsAnyPlanClicked;
}

long long UpsellPlans::getTransferFinishTime() const
{
    return mTransferFinishTime;
}

bool UpsellPlans::isOnlyProFlexiAvailable() const
{
    return mIsOnlyProFlexiAvailable;
}

bool UpsellPlans::isPro() const
{
    return mIsPro;
}

bool UpsellPlans::isMonthly() const
{
    return mIsMonthly;
}

void UpsellPlans::setMonthly(bool monthly)
{
    if (mIsMonthly != monthly)
    {
        mIsMonthly = monthly;
        emit monthlyChanged();
    }
}

void UpsellPlans::setBillingCurrency(bool isCurrencyBilling)
{
    if (mIsBillingCurrency != isCurrencyBilling)
    {
        mIsBillingCurrency = isCurrencyBilling;
        emit isCurrencyBillingChanged();
    }
}

void UpsellPlans::setCurrentDiscount(int discount)
{
    if (mCurrentDiscount != discount)
    {
        mCurrentDiscount = discount;
        emit currentDiscountChanged();
    }
}

void UpsellPlans::setTransferRemainingTime(const QString& time)
{
    if (mTransferRemainingTime != time)
    {
        mTransferRemainingTime = time;
        emit remainingTimeChanged();
    }
}

void UpsellPlans::setViewMode(ViewMode viewMode)
{
    if (mViewMode != viewMode)
    {
        mViewMode = viewMode;
        emit viewModeChanged();
    }
}

bool UpsellPlans::isBillingCurrency() const
{
    return mIsBillingCurrency;
}

int UpsellPlans::getCurrentDiscount() const
{
    return mCurrentDiscount;
}

QList<std::shared_ptr<UpsellPlans::Data>> UpsellPlans::plans() const
{
    return mPlans;
}

// ************************************************************************************************
// * UpsellPlans::Data
// ************************************************************************************************

UpsellPlans::Data::Data(int proLevel, const QString& name):
    mProLevel(proLevel),
    mRecommended(false),
    mName(name)
{}

QHash<int, QByteArray> UpsellPlans::Data::roleNames()
{
    static QHash<int, QByteArray> roles{
        {Qt::DisplayRole,                                "display"                  },
        {UpsellPlans::NAME_ROLE,                         "name"                     },
        {UpsellPlans::BUTTON_NAME_ROLE,                  "buttonName"               },
        {UpsellPlans::RECOMMENDED_ROLE,                  "recommended"              },
        {UpsellPlans::STORAGE_ROLE,                      "gbStorage"                },
        {UpsellPlans::TRANSFER_ROLE,                     "gbTransfer"               },
        {UpsellPlans::PRICE_ROLE,                        "price"                    },
        {UpsellPlans::TOTAL_PRICE_WITHOUT_DISCOUNT_ROLE, "totalPriceWithoutDiscount"},
        {UpsellPlans::MONTHLY_PRICE_WITH_DISCOUNT_ROLE,  "monthlyPriceWithDiscount" },
        {UpsellPlans::CURRENT_PLAN_ROLE,                 "currentPlan"              },
        {UpsellPlans::AVAILABLE_ROLE,                    "available"                },
        {UpsellPlans::SHOW_PRO_FLEXI_MESSAGE,            "showProFlexiMessage"      },
        {UpsellPlans::SHOW_ONLY_PRO_FLEXI,               "showOnlyProFlexi"         }
    };

    return roles;
}

int UpsellPlans::Data::proLevel() const
{
    return mProLevel;
}

bool UpsellPlans::Data::isRecommended() const
{
    return mRecommended;
}

const QString& UpsellPlans::Data::name() const
{
    return mName;
}

const UpsellPlans::Data::AccountBillingPlanData& UpsellPlans::Data::monthlyData() const
{
    return mMonthlyData;
}

const UpsellPlans::Data::AccountBillingPlanData& UpsellPlans::Data::yearlyData() const
{
    return mYearlyData;
}

void UpsellPlans::Data::setProLevel(int newProLevel)
{
    mProLevel = newProLevel;
}

void UpsellPlans::Data::setYearlyData(const AccountBillingPlanData& newYearlyData)
{
    mYearlyData = newYearlyData;
}

void UpsellPlans::Data::setName(const QString& name)
{
    mName = name;
}

void UpsellPlans::Data::setRecommended(bool newRecommended)
{
    mRecommended = newRecommended;
}

void UpsellPlans::Data::setMonthlyData(const AccountBillingPlanData& newMonthlyData)
{
    mMonthlyData = newMonthlyData;
}

// ************************************************************************************************
// * UpsellPlans::Data::AccountBillingPlanData
// ************************************************************************************************

UpsellPlans::Data::AccountBillingPlanData::AccountBillingPlanData():
    mGBStorage(-1),
    mGBTransfer(-1),
    mPrice(-1.0f)
{}

UpsellPlans::Data::AccountBillingPlanData::AccountBillingPlanData(int64_t gbStorage,
                                                                  int64_t gbTransfer,
                                                                  float price):
    mGBStorage(gbStorage),
    mGBTransfer(gbTransfer),
    mPrice(price)
{}

bool UpsellPlans::Data::AccountBillingPlanData::isValid() const
{
    return mGBStorage != -1 && mGBTransfer != -1 && mPrice != -1.0f;
}

int64_t UpsellPlans::Data::AccountBillingPlanData::gBStorage() const
{
    return mGBStorage;
}

int64_t UpsellPlans::Data::AccountBillingPlanData::gBTransfer() const
{
    return mGBTransfer;
}

float UpsellPlans::Data::AccountBillingPlanData::price() const
{
    return mPrice;
}

// ************************************************************************************************
// * UpsellPlans::CurrencyData
// ************************************************************************************************

QString UpsellPlans::CurrencyData::currencySymbol() const
{
    return mCurrencySymbol;
}

QString UpsellPlans::CurrencyData::currencyName() const
{
    return mCurrencyName;
}

void UpsellPlans::CurrencyData::setCurrencyName(const QString& newCurrencyName)
{
    mCurrencyName = newCurrencyName;
}

void UpsellPlans::CurrencyData::setCurrencySymbol(const QString& newCurrencySymbol)
{
    mCurrencySymbol = newCurrencySymbol;
}
