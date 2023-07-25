# Call Power Automate actions from the Web API

Dataverse contains a feature that allows power users to create their own custom sets of business logic called actions. From a developer perspective, Microsoft Learn defines an action as a "reusable operation, which may have observable side effects." These side effects include creating or updating records.

Another feature of actions is their ability to be invoked through the Web API. As a result, you can encapsulate your low-code automations in such a way that you can use them in nearly any scenario by interacting with them through their associated Web API request and response.

While this lesson doesn't cover how to create actions in detail, it's assumed that you already have a basic understanding of how to build them. If you need more information on how to create an action, you can review the documentation on them. See the Create Custom APIs section for detailed information on how to build Dataverse actions.

## Run actions with the Web API
When a new action is created in your Dataverse solution, the framework also creates a corresponding Web API request message.

## Call pre-built Dataverse actions
Dataverse comes with a set of existing actions that you can use to perform common operations. Some of these actions might only apply to model-driven or Dynamics 365 apps. For example, the CalculatePrice action calculates the price in an opportunity/quote/order/invoice, so it would only apply to a Dynamics 365 Sales app where that functionality exists.

For more information about which pre-built actions are available for use through the Web API, see the Web API Action Reference.

## Unbound vs. bound actions
An action can be built as either unbound (meaning, it doesn't have a Dataverse entity correlated to it) or bound (meaning, the logic is tied to a specific entity record). SQL developers could
consider these actions as similar to stored procedures (unbound actions) versus triggers (bound actions). However, unlike SQL triggers, you can also run bound actions on demand by providing a corresponding entity record ID as its parameter.

Unbound actions are beneficial for generic logic that might need to run outside the context of a specific entity record, such as the WinOpportunity action that was referenced earlier.

