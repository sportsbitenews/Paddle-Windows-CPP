#pragma once

#ifdef PADDLE_STATIC
	#define DECLSPEC	
#else
	#ifdef PADDLE_EXPORTS	// VS sets project name exports automatically
	#define DECLSPEC    __declspec(dllexport)
	#else
	#define DECLSPEC    __declspec(dllimport)
	#endif
#endif

namespace PaddleSDK
{
	class DECLSPEC Paddle
	{
	private:
		// Singleton PaddleSDK for those that wish to use it (can init direct if they dont)
		static Paddle * singleton;

		const char * apiKey;
		const char * productId;
		const char * vendorId;

		struct PaddleSDKInternals;
		PaddleSDKInternals * d_ptr;

	public:
		// Initialises a shared singleton version of the Paddle SDK
		static Paddle * initSharedInstance(const char *apiKey, const char *productId, const char *vendorId);
		// Fetches a previously initialised singleton
		static Paddle * getSharedInstance();

		// Creates a new instance of the Paddle SDK for the given credentials
		Paddle(const char *apiKey, const char *productId, const char *vendorId);

		// Sets default product information for use on first run
		void setProductData(const char *productName, const char *developerName, double productPriceUSD, int trialLength, const char *imagePath);
		void setProductData(LPWSTR productName, LPWSTR developerName, double productPriceUSD, int trialLength, LPWSTR imagePath);

		// Called once per app start
		void startLicencing(bool timeTrial);

		// Returns true if the product has been activated successfully by your customer
		bool productActivated();

		// Deactivate the current licence
		bool deactivateLicence();

		// Returns number of days remaining on this users trial. If startLicencing has not been successful, or a user's trial has expired then this will return 0
		int getDaysRemainingOnTrial();

		// Gets the duration of this users trial in days. Will default to 0 days if startLicencing has not been successful
		int getTrialLength();

		// Used to show the licencing process to the user
		void showLicensingWindow();

		//Start the purchase process directly
		void startPurchase();

		//Override price (USD)
		void overridePrice(double price);

		//Allow continued use of app after end of trial
		void setContinueOnTrialEnd(bool trialContinue);

		//Get email and licence code used for activation
		LPCWSTR activatedEmail();
		LPCWSTR activatedLicence();
	};
}