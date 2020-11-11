

// Patron singleton con mejoras (Create(), Destroy())

class MiSingleton
{
private:
	MiSingleton() {}
	
public:

  static MiSingleton& GetInstance()
  {
    if (!m_pInstance)
    {
      // warning!!
      // Exit
    }
    return *m_pInstance;
  }

  static void Create()
  {
    if (!m_pInstance)
    {
      m_pInstance = new MiSingleton();
    }
  }

  static void Destroy()
  {
    if (!m_pInstance)
    {
      delete m_pInstance;
    }
  }

private:
  static MiSingleton* m_pInstance;
}


// Los constructores copia siempre explicit