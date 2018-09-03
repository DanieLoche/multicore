#include "job.h"
#include "processor.h"
#include "lists.h"

using namespace lists;

class scheduler {
	public:
		scheduler(bool _preemptive, std::string _policy,  bool _bestEffort, unsigned _processorsNumber, const std::vector<job>& jobs, int _unfeasibleJobsNumber); //construct
	private:
		bool checkIncomingJobs();				// this function release each scheduled job at the right time, returns true if one or more READY jobs are relased
		void dispatcher();							// add/preempt jobs to/from processors
		bool executeStep();							// makes each processor to execute one step: returns true if one or more jobs finish
		std::map<int,int> getProcessorsOrderedByJobId();				// returns a map with a link to the processors ordered by their current executing job Ids
		void printMachineTimeline();		// prints report of the machine behavior
		void printReport();							// prints the final report
		void step();										// it's like a clock
		void policySelecter(std::string);

		void FifoPolicy();
		void RoundRobinPolicy();
		bool preemptive;								// by default the machine is preemptive
		bool bestEffort;								// by default the machine is best effort (executes unfeasible jobs)
		std::function<void(void)> policy_fct;
		int clockStep;									// keeps track of the system time
		std::vector<processor> processors;			// array of system's processors
		std::vector<job> jobs;									// array of system's jobs
		int jobsThatNotMetTheirDeadline;				// current jobs number that finished after their deadline
		int unfeasibleJobsNumber;								// current unfeasible jobs number
		unsigned totalJobsNumber;								// total number of jobs in the system
};
