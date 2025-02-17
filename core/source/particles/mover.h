////////////////////////////////////////
// Mover Tool - assembles and invokes //
// BundleMover objects                //
////////////////////////////////////////

struct Mover:ComputeTool
{
	tw::Float q0,m0;
	tw::Int ignorable[4];
	// Following particles and fields are owned by the parent Species module
	std::vector<Particle> *particle;
	std::vector<TransferParticle> *transfer;
	Field *ESField,*EM,*sources,*laser,*chi,*qo_j4;
	Mover(const std::string& name,MetricSpace *m,Task *tsk);
	void AddTransferParticle(const Particle& src);
	void GetSubarrayBounds(std::vector<ParticleRef>& sorted,tw::Int low[4],tw::Int high[4],tw::Int layers);
	void SpreadTasks(std::vector<tw::Int>& task_map);
	void BunchTasks(std::vector<tw::Int>& task_map);
	template <class BundleType>
	void MoveSlice(tw::Int tasks,tw::Int tid,tw::Int bounds_data[][8]);
	template <class BundleType>
	void DoTasks();
	virtual void Advance();

	virtual void InitTest();
	virtual void MinimizePrimitiveScalarTest();
	virtual void MinimizePrimitiveVectorTest();
	virtual void TranslationTest();
	virtual bool Test();
	virtual void CloseTest();
};

// Subclasses of the Mover Tool
// These are simple dispatchers. Their only purpose is to make the
// appropriate templated call to DoTasks().  The template argument is one
// of the BundleMover* classes.

struct BorisMover:Mover
{
	BorisMover(const std::string& name,MetricSpace *m,Task *tsk): Mover(name,m,tsk) {}
	virtual void Advance();
	virtual void InitTest();
};

struct UnitaryMover:Mover
{
	UnitaryMover(const std::string& name,MetricSpace *m,Task *tsk): Mover(name,m,tsk) {}
	virtual void Advance();
	virtual bool Test() { return false; }
};

struct PGCMover:Mover
{
	PGCMover(const std::string& name,MetricSpace *m,Task *tsk): Mover(name,m,tsk) {}
	virtual void Advance();
	virtual void InitTest();
};

struct BohmianMover:Mover
{
	BohmianMover(const std::string& name,MetricSpace *m,Task *tsk): Mover(name,m,tsk) {}
	virtual void Advance();
	virtual bool Test() { return false; }
};

/////////////////////////////////////
// Bundle Movers - pusher + tiler  //
// These are created by the mover  //
// tool, and invoked by template   //
/////////////////////////////////////

struct BundleMoverBoris2D : BundleTilerEM2D,BundlePusherBoris
{
	BundleMoverBoris2D(Mover *owner) : BundleTilerEM2D(owner), BundlePusherBoris(owner), ParticleBundle(owner) {}
	void Move();
};

struct BundleMoverBoris3D : BundleTilerEM3D,BundlePusherBoris
{
	BundleMoverBoris3D(Mover *owner) : BundleTilerEM3D(owner), BundlePusherBoris(owner), ParticleBundle(owner) {}
	void Move();
};

struct BundleMoverUnitary2D : BundleTilerEM2D,BundlePusherUnitary
{
	BundleMoverUnitary2D(Mover *owner) : BundleTilerEM2D(owner), BundlePusherUnitary(owner), ParticleBundle(owner) {}
	void Move();
};

struct BundleMoverUnitary3D : BundleTilerEM3D,BundlePusherUnitary
{
	BundleMoverUnitary3D(Mover *owner) : BundleTilerEM3D(owner), BundlePusherUnitary(owner), ParticleBundle(owner) {}
	void Move();
};

struct BundleMoverPGC2D : BundleTilerPGC2D,BundleTilerEM2D,BundlePusherPGC
{
	BundleMoverPGC2D(Mover *owner) : BundleTilerPGC2D(owner), BundleTilerEM2D(owner), BundlePusherPGC(owner), ParticleBundle(owner) {}
	// For PGC we have to call two slicers explicitly
	void LoadFieldSlice(tw::Int low[4],tw::Int high[4],tw::Int ignorable[4]);
	void InitSourceSlice(tw::Int low[4],tw::Int high[4],tw::Int ignorable[4]);
	void DepositSourceSlice(bool needsAtomic);
	void Move();
};

struct BundleMoverPGC3D : BundleTilerPGC3D,BundleTilerEM3D,BundlePusherPGC
{
	BundleMoverPGC3D(Mover *owner) : BundleTilerPGC3D(owner), BundleTilerEM3D(owner), BundlePusherPGC(owner), ParticleBundle(owner) {}
	// For PGC we have to call two slicers explicitly
	void LoadFieldSlice(tw::Int low[4],tw::Int high[4],tw::Int ignorable[4]);
	void InitSourceSlice(tw::Int low[4],tw::Int high[4],tw::Int ignorable[4]);
	void DepositSourceSlice(bool needsAtomic);
	void Move();
};

struct BundleMoverBohmian2D : BundleTilerBohmian2D,BundlePusherBohmian
{
	BundleMoverBohmian2D(Mover *owner) : BundleTilerBohmian2D(owner), BundlePusherBohmian(owner), ParticleBundle(owner) {}
	void Move();
};

struct BundleMoverBohmian3D : BundleTilerBohmian3D,BundlePusherBohmian
{
	BundleMoverBohmian3D(Mover *owner) : BundleTilerBohmian3D(owner), BundlePusherBohmian(owner), ParticleBundle(owner) {}
	void Move();
};
