import FWCore.ParameterSet.Config as cms

process = cms.Process("Demo")

process.load("Tests.MaterialNtuplizer.commonIncludes_example_cff")

## Top level replacement
#from Configuration.GlobalRuns.customise_Collision_38X import customise
#customise(process)

process.GlobalTag.globaltag = 'START311_V2::All'





readFiles = cms.untracked.vstring(
        '/store/mc/Summer11/MinBias_TuneZ2_7TeV-pythia6/GEN-SIM-RECODEBUG/START311_V2_0T-v2/0000/FE683904-8454-E011-A10E-E0CB4E55368D.root',
        '/store/mc/Summer11/MinBias_TuneZ2_7TeV-pythia6/GEN-SIM-RECODEBUG/START311_V2_0T-v2/0000/FCD7829A-5054-E011-9FD5-E0CB4E553676.root',
        '/store/mc/Summer11/MinBias_TuneZ2_7TeV-pythia6/GEN-SIM-RECODEBUG/START311_V2_0T-v2/0000/FC670EA2-5054-E011-BC1A-001A4BA650A4.root',
        '/store/mc/Summer11/MinBias_TuneZ2_7TeV-pythia6/GEN-SIM-RECODEBUG/START311_V2_0T-v2/0000/FACA95C7-6A54-E011-AEC1-0022198F5B1E.root',
        '/store/mc/Summer11/MinBias_TuneZ2_7TeV-pythia6/GEN-SIM-RECODEBUG/START311_V2_0T-v2/0000/FA9E8EB3-9354-E011-99AD-00261834B569.root',
        '/store/mc/Summer11/MinBias_TuneZ2_7TeV-pythia6/GEN-SIM-RECODEBUG/START311_V2_0T-v2/0000/FA15CCFE-7A54-E011-B343-90E6BA0D09B2.root',
        '/store/mc/Summer11/MinBias_TuneZ2_7TeV-pythia6/GEN-SIM-RECODEBUG/START311_V2_0T-v2/0000/EE2F910A-BA54-E011-8A4F-E0CB4E19F96D.root',
        '/store/mc/Summer11/MinBias_TuneZ2_7TeV-pythia6/GEN-SIM-RECODEBUG/START311_V2_0T-v2/0000/EC67275E-4F54-E011-BF02-001A4BA64186.root',
        '/store/mc/Summer11/MinBias_TuneZ2_7TeV-pythia6/GEN-SIM-RECODEBUG/START311_V2_0T-v2/0000/EADDAEED-7D54-E011-9336-E0CB4E55368D.root',
        '/store/mc/Summer11/MinBias_TuneZ2_7TeV-pythia6/GEN-SIM-RECODEBUG/START311_V2_0T-v2/0000/E842213B-6A54-E011-9918-E0CB4E1A119A.root',
        '/store/mc/Summer11/MinBias_TuneZ2_7TeV-pythia6/GEN-SIM-RECODEBUG/START311_V2_0T-v2/0000/E67188C4-7E54-E011-9FE1-90E6BA19A22B.root',
        '/store/mc/Summer11/MinBias_TuneZ2_7TeV-pythia6/GEN-SIM-RECODEBUG/START311_V2_0T-v2/0000/E2DB96C3-7E54-E011-B5C9-90E6BA19A258.root',
        '/store/mc/Summer11/MinBias_TuneZ2_7TeV-pythia6/GEN-SIM-RECODEBUG/START311_V2_0T-v2/0000/E257237F-7E54-E011-AE81-00261834B51E.root',
        '/store/mc/Summer11/MinBias_TuneZ2_7TeV-pythia6/GEN-SIM-RECODEBUG/START311_V2_0T-v2/0000/E0013FF1-4D54-E011-87CD-0030487CB568.root',
        '/store/mc/Summer11/MinBias_TuneZ2_7TeV-pythia6/GEN-SIM-RECODEBUG/START311_V2_0T-v2/0000/DC2BF13C-7554-E011-BAB1-485B39800B62.root',
        '/store/mc/Summer11/MinBias_TuneZ2_7TeV-pythia6/GEN-SIM-RECODEBUG/START311_V2_0T-v2/0000/DA4E1752-7D54-E011-A272-E0CB4E29C50D.root',
        '/store/mc/Summer11/MinBias_TuneZ2_7TeV-pythia6/GEN-SIM-RECODEBUG/START311_V2_0T-v2/0000/D8E76489-7554-E011-8382-E0CB4E29C4D6.root',
        '/store/mc/Summer11/MinBias_TuneZ2_7TeV-pythia6/GEN-SIM-RECODEBUG/START311_V2_0T-v2/0000/D6026D3C-6A54-E011-AD90-00221993098A.root',
        '/store/mc/Summer11/MinBias_TuneZ2_7TeV-pythia6/GEN-SIM-RECODEBUG/START311_V2_0T-v2/0000/D24A1890-9054-E011-9902-001A4BA964FA.root',
        '/store/mc/Summer11/MinBias_TuneZ2_7TeV-pythia6/GEN-SIM-RECODEBUG/START311_V2_0T-v2/0000/C8D8F824-7454-E011-9331-E0CB4E1A115D.root',
        '/store/mc/Summer11/MinBias_TuneZ2_7TeV-pythia6/GEN-SIM-RECODEBUG/START311_V2_0T-v2/0000/C8B17998-6A54-E011-BC69-485B39800BB9.root',
        '/store/mc/Summer11/MinBias_TuneZ2_7TeV-pythia6/GEN-SIM-RECODEBUG/START311_V2_0T-v2/0000/C69F2105-7454-E011-ABA6-E0CB4EA0A92A.root',
        '/store/mc/Summer11/MinBias_TuneZ2_7TeV-pythia6/GEN-SIM-RECODEBUG/START311_V2_0T-v2/0000/C687CFFF-6A54-E011-9B9E-001A4BA54360.root',
        '/store/mc/Summer11/MinBias_TuneZ2_7TeV-pythia6/GEN-SIM-RECODEBUG/START311_V2_0T-v2/0000/C47A31F8-6A54-E011-8F9E-E0CB4E29C4D3.root',
        '/store/mc/Summer11/MinBias_TuneZ2_7TeV-pythia6/GEN-SIM-RECODEBUG/START311_V2_0T-v2/0000/C4620B24-6954-E011-9CCD-E0CB4EA0A8EC.root',
        '/store/mc/Summer11/MinBias_TuneZ2_7TeV-pythia6/GEN-SIM-RECODEBUG/START311_V2_0T-v2/0000/C28957C6-8C54-E011-A3EE-001A4BA82FF8.root',
        '/store/mc/Summer11/MinBias_TuneZ2_7TeV-pythia6/GEN-SIM-RECODEBUG/START311_V2_0T-v2/0000/C21BDD17-7454-E011-9B7D-001EC9D8D08D.root',
        '/store/mc/Summer11/MinBias_TuneZ2_7TeV-pythia6/GEN-SIM-RECODEBUG/START311_V2_0T-v2/0000/BE584446-6954-E011-8CC5-E0CB4E19F9AC.root',
        '/store/mc/Summer11/MinBias_TuneZ2_7TeV-pythia6/GEN-SIM-RECODEBUG/START311_V2_0T-v2/0000/BAF77C3C-7C54-E011-BD72-90E6BA442F0A.root',
        '/store/mc/Summer11/MinBias_TuneZ2_7TeV-pythia6/GEN-SIM-RECODEBUG/START311_V2_0T-v2/0000/B42D8847-7C54-E011-8EEC-001A4BA6A818.root',
        '/store/mc/Summer11/MinBias_TuneZ2_7TeV-pythia6/GEN-SIM-RECODEBUG/START311_V2_0T-v2/0000/B0B882F1-6954-E011-87C9-E0CB4EA0A8E0.root',
        '/store/mc/Summer11/MinBias_TuneZ2_7TeV-pythia6/GEN-SIM-RECODEBUG/START311_V2_0T-v2/0000/B05E5808-B454-E011-B510-90E6BA442F16.root',
        '/store/mc/Summer11/MinBias_TuneZ2_7TeV-pythia6/GEN-SIM-RECODEBUG/START311_V2_0T-v2/0000/AEE74D69-8B54-E011-AF3E-90E6BAE8CC20.root',
        '/store/mc/Summer11/MinBias_TuneZ2_7TeV-pythia6/GEN-SIM-RECODEBUG/START311_V2_0T-v2/0000/ACD230BD-7554-E011-A664-485B39800C02.root',
        '/store/mc/Summer11/MinBias_TuneZ2_7TeV-pythia6/GEN-SIM-RECODEBUG/START311_V2_0T-v2/0000/AC6C4F60-6A54-E011-848B-90E6BA442F05.root',
        '/store/mc/Summer11/MinBias_TuneZ2_7TeV-pythia6/GEN-SIM-RECODEBUG/START311_V2_0T-v2/0000/AA2CF818-6954-E011-AC95-E0CB4E553667.root',
        '/store/mc/Summer11/MinBias_TuneZ2_7TeV-pythia6/GEN-SIM-RECODEBUG/START311_V2_0T-v2/0000/A8558FAC-7154-E011-9ED6-E0CB4E29C4D3.root',
        '/store/mc/Summer11/MinBias_TuneZ2_7TeV-pythia6/GEN-SIM-RECODEBUG/START311_V2_0T-v2/0000/A6728199-7C54-E011-91F8-E0CB4E29C4F7.root',
        '/store/mc/Summer11/MinBias_TuneZ2_7TeV-pythia6/GEN-SIM-RECODEBUG/START311_V2_0T-v2/0000/A4B20E5A-7D54-E011-8C10-E0CB4E1A116C.root',
        '/store/mc/Summer11/MinBias_TuneZ2_7TeV-pythia6/GEN-SIM-RECODEBUG/START311_V2_0T-v2/0000/A2B93ED3-7454-E011-938F-E0CB4EA0A8FA.root',
        '/store/mc/Summer11/MinBias_TuneZ2_7TeV-pythia6/GEN-SIM-RECODEBUG/START311_V2_0T-v2/0000/A212C5EF-7D54-E011-9B16-E0CB4E29C4B9.root',
        '/store/mc/Summer11/MinBias_TuneZ2_7TeV-pythia6/GEN-SIM-RECODEBUG/START311_V2_0T-v2/0000/A0B57747-6954-E011-9A41-E0CB4E1A1179.root',
        '/store/mc/Summer11/MinBias_TuneZ2_7TeV-pythia6/GEN-SIM-RECODEBUG/START311_V2_0T-v2/0000/A06879FD-8A54-E011-BAA0-485B39800BD5.root',
        '/store/mc/Summer11/MinBias_TuneZ2_7TeV-pythia6/GEN-SIM-RECODEBUG/START311_V2_0T-v2/0000/9E6C8281-D354-E011-9F1A-E0CB4E1A1190.root',
        '/store/mc/Summer11/MinBias_TuneZ2_7TeV-pythia6/GEN-SIM-RECODEBUG/START311_V2_0T-v2/0000/9CABCE4F-9054-E011-B116-001A4BA533AC.root',
        '/store/mc/Summer11/MinBias_TuneZ2_7TeV-pythia6/GEN-SIM-RECODEBUG/START311_V2_0T-v2/0000/9C11FB62-4F54-E011-9D4E-0019BB3FE352.root',
        '/store/mc/Summer11/MinBias_TuneZ2_7TeV-pythia6/GEN-SIM-RECODEBUG/START311_V2_0T-v2/0000/96381608-6954-E011-ADC5-001A4BA5815C.root',
        '/store/mc/Summer11/MinBias_TuneZ2_7TeV-pythia6/GEN-SIM-RECODEBUG/START311_V2_0T-v2/0000/94827EFD-6854-E011-8A7E-E0CB4E1A116D.root',
        '/store/mc/Summer11/MinBias_TuneZ2_7TeV-pythia6/GEN-SIM-RECODEBUG/START311_V2_0T-v2/0000/929C4841-7554-E011-A1DE-001A4BA92916.root',
        '/store/mc/Summer11/MinBias_TuneZ2_7TeV-pythia6/GEN-SIM-RECODEBUG/START311_V2_0T-v2/0000/90C9E196-6A54-E011-BDDC-00261834B53D.root',
        '/store/mc/Summer11/MinBias_TuneZ2_7TeV-pythia6/GEN-SIM-RECODEBUG/START311_V2_0T-v2/0000/9091670D-7454-E011-9B64-E0CB4E29C4C9.root',
        '/store/mc/Summer11/MinBias_TuneZ2_7TeV-pythia6/GEN-SIM-RECODEBUG/START311_V2_0T-v2/0000/8EB66165-0355-E011-AFB4-E0CB4EA0A908.root',
        '/store/mc/Summer11/MinBias_TuneZ2_7TeV-pythia6/GEN-SIM-RECODEBUG/START311_V2_0T-v2/0000/8E98E6ED-6954-E011-9D01-E0CB4E4408BE.root',
        '/store/mc/Summer11/MinBias_TuneZ2_7TeV-pythia6/GEN-SIM-RECODEBUG/START311_V2_0T-v2/0000/8A627D36-7E54-E011-9953-E0CB4E5536A5.root',
        '/store/mc/Summer11/MinBias_TuneZ2_7TeV-pythia6/GEN-SIM-RECODEBUG/START311_V2_0T-v2/0000/863CBB7B-7554-E011-98BF-90E6BA0D0998.root',
        '/store/mc/Summer11/MinBias_TuneZ2_7TeV-pythia6/GEN-SIM-RECODEBUG/START311_V2_0T-v2/0000/84D2BFEC-6B54-E011-9CAB-003048D28EB2.root',
        '/store/mc/Summer11/MinBias_TuneZ2_7TeV-pythia6/GEN-SIM-RECODEBUG/START311_V2_0T-v2/0000/84B2B3D4-6954-E011-925E-E0CB4E29C4FF.root',
        '/store/mc/Summer11/MinBias_TuneZ2_7TeV-pythia6/GEN-SIM-RECODEBUG/START311_V2_0T-v2/0000/84866AE8-6B54-E011-84EE-E0CB4E1A1144.root',
        '/store/mc/Summer11/MinBias_TuneZ2_7TeV-pythia6/GEN-SIM-RECODEBUG/START311_V2_0T-v2/0000/8064F15D-B354-E011-BB0A-001A4BA87F02.root',
        '/store/mc/Summer11/MinBias_TuneZ2_7TeV-pythia6/GEN-SIM-RECODEBUG/START311_V2_0T-v2/0000/7E9E15E5-6B54-E011-B383-E0CB4E19F969.root',
        '/store/mc/Summer11/MinBias_TuneZ2_7TeV-pythia6/GEN-SIM-RECODEBUG/START311_V2_0T-v2/0000/7E1190AB-7154-E011-A32D-E0CB4E29C4BE.root',
        '/store/mc/Summer11/MinBias_TuneZ2_7TeV-pythia6/GEN-SIM-RECODEBUG/START311_V2_0T-v2/0000/7E0C2EAE-7154-E011-BF7F-E0CB4E29C51F.root',
        '/store/mc/Summer11/MinBias_TuneZ2_7TeV-pythia6/GEN-SIM-RECODEBUG/START311_V2_0T-v2/0000/7AE0AFDD-6854-E011-BD3A-90E6BA442F3B.root',
        '/store/mc/Summer11/MinBias_TuneZ2_7TeV-pythia6/GEN-SIM-RECODEBUG/START311_V2_0T-v2/0000/7A923052-7B54-E011-B12E-001A4BA92916.root',
        '/store/mc/Summer11/MinBias_TuneZ2_7TeV-pythia6/GEN-SIM-RECODEBUG/START311_V2_0T-v2/0000/7497673C-6A54-E011-975C-90E6BA442F3F.root',
        '/store/mc/Summer11/MinBias_TuneZ2_7TeV-pythia6/GEN-SIM-RECODEBUG/START311_V2_0T-v2/0000/740373D4-6954-E011-A996-E0CB4E29C4DE.root',
        '/store/mc/Summer11/MinBias_TuneZ2_7TeV-pythia6/GEN-SIM-RECODEBUG/START311_V2_0T-v2/0000/72F390E4-6B54-E011-AB4C-E0CB4E19F975.root',
        '/store/mc/Summer11/MinBias_TuneZ2_7TeV-pythia6/GEN-SIM-RECODEBUG/START311_V2_0T-v2/0000/72300C85-7C54-E011-A44A-E0CB4E19F959.root',
        '/store/mc/Summer11/MinBias_TuneZ2_7TeV-pythia6/GEN-SIM-RECODEBUG/START311_V2_0T-v2/0000/72064C08-8454-E011-9C07-00261834B5D2.root',
        '/store/mc/Summer11/MinBias_TuneZ2_7TeV-pythia6/GEN-SIM-RECODEBUG/START311_V2_0T-v2/0000/70DC44B6-9054-E011-BE3D-90E6BA0D09EA.root',
        '/store/mc/Summer11/MinBias_TuneZ2_7TeV-pythia6/GEN-SIM-RECODEBUG/START311_V2_0T-v2/0000/6CA657FF-7354-E011-BAEB-E0CB4E553656.root',
        '/store/mc/Summer11/MinBias_TuneZ2_7TeV-pythia6/GEN-SIM-RECODEBUG/START311_V2_0T-v2/0000/6C2156AB-7154-E011-BBFB-E0CB4E29C4D6.root',
        '/store/mc/Summer11/MinBias_TuneZ2_7TeV-pythia6/GEN-SIM-RECODEBUG/START311_V2_0T-v2/0000/6A6A953D-9054-E011-898E-E0CB4E19F972.root',
        '/store/mc/Summer11/MinBias_TuneZ2_7TeV-pythia6/GEN-SIM-RECODEBUG/START311_V2_0T-v2/0000/667FD589-7554-E011-9236-E0CB4E29C4D5.root',
        '/store/mc/Summer11/MinBias_TuneZ2_7TeV-pythia6/GEN-SIM-RECODEBUG/START311_V2_0T-v2/0000/64F4E62C-6C54-E011-93B6-90E6BA19A241.root',
        '/store/mc/Summer11/MinBias_TuneZ2_7TeV-pythia6/GEN-SIM-RECODEBUG/START311_V2_0T-v2/0000/641C69B3-EF54-E011-8EDB-485B39800BF3.root',
        '/store/mc/Summer11/MinBias_TuneZ2_7TeV-pythia6/GEN-SIM-RECODEBUG/START311_V2_0T-v2/0000/640F394A-6954-E011-A945-E0CB4E1A116E.root',
        '/store/mc/Summer11/MinBias_TuneZ2_7TeV-pythia6/GEN-SIM-RECODEBUG/START311_V2_0T-v2/0000/5EAA0024-7454-E011-ACD8-90E6BA442EF4.root',
        '/store/mc/Summer11/MinBias_TuneZ2_7TeV-pythia6/GEN-SIM-RECODEBUG/START311_V2_0T-v2/0000/5A627EAE-7154-E011-BCD8-90E6BA19A20E.root',
        '/store/mc/Summer11/MinBias_TuneZ2_7TeV-pythia6/GEN-SIM-RECODEBUG/START311_V2_0T-v2/0000/58C7CFED-7D54-E011-9110-00261834B5C6.root',
        '/store/mc/Summer11/MinBias_TuneZ2_7TeV-pythia6/GEN-SIM-RECODEBUG/START311_V2_0T-v2/0000/54A985A2-4E54-E011-8077-90E6BA19A243.root',
        '/store/mc/Summer11/MinBias_TuneZ2_7TeV-pythia6/GEN-SIM-RECODEBUG/START311_V2_0T-v2/0000/5461F0D2-6954-E011-819A-E0CB4E29C4D0.root',
        '/store/mc/Summer11/MinBias_TuneZ2_7TeV-pythia6/GEN-SIM-RECODEBUG/START311_V2_0T-v2/0000/54313B3A-6A54-E011-8C6E-485B39800BB4.root',
        '/store/mc/Summer11/MinBias_TuneZ2_7TeV-pythia6/GEN-SIM-RECODEBUG/START311_V2_0T-v2/0000/50B747E2-8D54-E011-A615-E0CB4E4408DF.root',
        '/store/mc/Summer11/MinBias_TuneZ2_7TeV-pythia6/GEN-SIM-RECODEBUG/START311_V2_0T-v2/0000/4EE570A5-5254-E011-83A3-E0CB4E553640.root',
        '/store/mc/Summer11/MinBias_TuneZ2_7TeV-pythia6/GEN-SIM-RECODEBUG/START311_V2_0T-v2/0000/4E9AA2A5-5254-E011-8274-E0CB4E29C4E9.root',
        '/store/mc/Summer11/MinBias_TuneZ2_7TeV-pythia6/GEN-SIM-RECODEBUG/START311_V2_0T-v2/0000/4A6E3229-A154-E011-82CA-E0CB4E553640.root',
        '/store/mc/Summer11/MinBias_TuneZ2_7TeV-pythia6/GEN-SIM-RECODEBUG/START311_V2_0T-v2/0000/48C18757-5454-E011-9B5B-E0CB4E5536D7.root',
        '/store/mc/Summer11/MinBias_TuneZ2_7TeV-pythia6/GEN-SIM-RECODEBUG/START311_V2_0T-v2/0000/44EA713C-6A54-E011-94D2-90E6BA0D09B8.root',
        '/store/mc/Summer11/MinBias_TuneZ2_7TeV-pythia6/GEN-SIM-RECODEBUG/START311_V2_0T-v2/0000/443D6ECA-7D54-E011-842D-001A4BA566A6.root',
        '/store/mc/Summer11/MinBias_TuneZ2_7TeV-pythia6/GEN-SIM-RECODEBUG/START311_V2_0T-v2/0000/420EC024-8A54-E011-8E4F-E0CB4EA0A932.root',
        '/store/mc/Summer11/MinBias_TuneZ2_7TeV-pythia6/GEN-SIM-RECODEBUG/START311_V2_0T-v2/0000/3C83CE6B-9354-E011-9BB3-0022198F5B1E.root',
        '/store/mc/Summer11/MinBias_TuneZ2_7TeV-pythia6/GEN-SIM-RECODEBUG/START311_V2_0T-v2/0000/38E3CFC6-4E54-E011-B728-E0CB4E4408EC.root',
        '/store/mc/Summer11/MinBias_TuneZ2_7TeV-pythia6/GEN-SIM-RECODEBUG/START311_V2_0T-v2/0000/380EBC01-6B54-E011-9584-0019BB3FF40C.root',
        '/store/mc/Summer11/MinBias_TuneZ2_7TeV-pythia6/GEN-SIM-RECODEBUG/START311_V2_0T-v2/0000/36994EA3-5354-E011-BCBE-001EC9D87221.root',
        '/store/mc/Summer11/MinBias_TuneZ2_7TeV-pythia6/GEN-SIM-RECODEBUG/START311_V2_0T-v2/0000/34FBF224-6954-E011-83AB-485B39800B94.root',
        '/store/mc/Summer11/MinBias_TuneZ2_7TeV-pythia6/GEN-SIM-RECODEBUG/START311_V2_0T-v2/0000/34FBD7AF-7154-E011-8D16-0022198F5AF3.root',
        '/store/mc/Summer11/MinBias_TuneZ2_7TeV-pythia6/GEN-SIM-RECODEBUG/START311_V2_0T-v2/0000/34006A7F-7E54-E011-884D-90E6BA19A23E.root',
        '/store/mc/Summer11/MinBias_TuneZ2_7TeV-pythia6/GEN-SIM-RECODEBUG/START311_V2_0T-v2/0000/2A81D625-5454-E011-ABF1-0019BB3FE352.root',
        '/store/mc/Summer11/MinBias_TuneZ2_7TeV-pythia6/GEN-SIM-RECODEBUG/START311_V2_0T-v2/0000/289511D1-8D54-E011-840E-E0CB4E29C4E7.root',
        '/store/mc/Summer11/MinBias_TuneZ2_7TeV-pythia6/GEN-SIM-RECODEBUG/START311_V2_0T-v2/0000/284CD599-7C54-E011-8D5F-E0CB4E1A1150.root',
        '/store/mc/Summer11/MinBias_TuneZ2_7TeV-pythia6/GEN-SIM-RECODEBUG/START311_V2_0T-v2/0000/24E07011-7554-E011-A0B5-00261834B59B.root',
        '/store/mc/Summer11/MinBias_TuneZ2_7TeV-pythia6/GEN-SIM-RECODEBUG/START311_V2_0T-v2/0000/22638F3F-6B54-E011-9842-E0CB4E29C507.root',
        '/store/mc/Summer11/MinBias_TuneZ2_7TeV-pythia6/GEN-SIM-RECODEBUG/START311_V2_0T-v2/0000/225C677E-7E54-E011-A02D-90E6BA19A1FE.root',
        '/store/mc/Summer11/MinBias_TuneZ2_7TeV-pythia6/GEN-SIM-RECODEBUG/START311_V2_0T-v2/0000/20DF7595-7D54-E011-8C45-90E6BA19A241.root',
        '/store/mc/Summer11/MinBias_TuneZ2_7TeV-pythia6/GEN-SIM-RECODEBUG/START311_V2_0T-v2/0000/20BA01F2-7D54-E011-9460-E0CB4E29C4D8.root',
        '/store/mc/Summer11/MinBias_TuneZ2_7TeV-pythia6/GEN-SIM-RECODEBUG/START311_V2_0T-v2/0000/1E5586FB-9754-E011-ABAC-0019BB3D48D4.root',
        '/store/mc/Summer11/MinBias_TuneZ2_7TeV-pythia6/GEN-SIM-RECODEBUG/START311_V2_0T-v2/0000/1C1EE248-6954-E011-A222-485B39800C16.root',
        '/store/mc/Summer11/MinBias_TuneZ2_7TeV-pythia6/GEN-SIM-RECODEBUG/START311_V2_0T-v2/0000/1AE20D28-CE54-E011-919C-0019BB36016C.root',
        '/store/mc/Summer11/MinBias_TuneZ2_7TeV-pythia6/GEN-SIM-RECODEBUG/START311_V2_0T-v2/0000/1ABBF636-6C54-E011-87A1-001A4BA5ABE2.root',
        '/store/mc/Summer11/MinBias_TuneZ2_7TeV-pythia6/GEN-SIM-RECODEBUG/START311_V2_0T-v2/0000/1A9E55B7-9054-E011-99A3-90E6BA442EF8.root',
        '/store/mc/Summer11/MinBias_TuneZ2_7TeV-pythia6/GEN-SIM-RECODEBUG/START311_V2_0T-v2/0000/1674B533-A154-E011-80B5-001A4BA9764C.root',
        '/store/mc/Summer11/MinBias_TuneZ2_7TeV-pythia6/GEN-SIM-RECODEBUG/START311_V2_0T-v2/0000/14FD0E2C-5054-E011-AF12-E0CB4E1A1185.root',
        '/store/mc/Summer11/MinBias_TuneZ2_7TeV-pythia6/GEN-SIM-RECODEBUG/START311_V2_0T-v2/0000/148F9F56-7B54-E011-9B5E-90E6BA442F00.root',
        '/store/mc/Summer11/MinBias_TuneZ2_7TeV-pythia6/GEN-SIM-RECODEBUG/START311_V2_0T-v2/0000/14398047-6954-E011-919C-E0CB4E1A1179.root',
        '/store/mc/Summer11/MinBias_TuneZ2_7TeV-pythia6/GEN-SIM-RECODEBUG/START311_V2_0T-v2/0000/0EE94EC6-9954-E011-9648-90E6BA442F1A.root',
        '/store/mc/Summer11/MinBias_TuneZ2_7TeV-pythia6/GEN-SIM-RECODEBUG/START311_V2_0T-v2/0000/0E48AFBC-7554-E011-9773-E0CB4EA0A933.root',
        '/store/mc/Summer11/MinBias_TuneZ2_7TeV-pythia6/GEN-SIM-RECODEBUG/START311_V2_0T-v2/0000/0CB9478F-6954-E011-B9C9-E0CB4E4408E9.root',
        '/store/mc/Summer11/MinBias_TuneZ2_7TeV-pythia6/GEN-SIM-RECODEBUG/START311_V2_0T-v2/0000/04F04BA6-6A54-E011-98B8-E0CB4E29C511.root',
        '/store/mc/Summer11/MinBias_TuneZ2_7TeV-pythia6/GEN-SIM-RECODEBUG/START311_V2_0T-v2/0000/04A2D1AD-7154-E011-A71A-E0CB4EA0A933.root',
        '/store/mc/Summer11/MinBias_TuneZ2_7TeV-pythia6/GEN-SIM-RECODEBUG/START311_V2_0T-v2/0000/0274A23C-6A54-E011-8F62-90E6BA442F05.root'
)

secFiles = cms.untracked.vstring()
source = cms.Source ("PoolSource",fileNames = readFiles, secondaryFileNames = secFiles)
process.source = source



process.maxEvents = cms.untracked.PSet(input = cms.untracked.int32(-1))

process.MessageLogger.cerr.FwkReport.reportEvery = cms.untracked.int32(1000)
process.options = cms.untracked.PSet( wantSummary = cms.untracked.bool(True) )

process.pixClus = cms.EDProducer("SiPixelClusterMultiplicityProducer",
                                 clusterdigiCollection = cms.InputTag("siPixelClusters"),
                                 wantedSubDets = cms.VPSet(    
                                 cms.PSet(detSelection = cms.uint32(0),detLabel = cms.string("Pixel")),
                                 cms.PSet(detSelection = cms.uint32(1),detLabel = cms.string("BPIX")),
                                 cms.PSet(detSelection = cms.uint32(2),detLabel = cms.string("FPIX")) 
                                 )
                                 )


process.tkClus = cms.EDProducer("SiStripClusterMultiplicityProducer",
                                   clusterdigiCollection = cms.InputTag("siStripClusters"),
                                   wantedSubDets = cms.VPSet(    
                                                          cms.PSet(detSelection = cms.uint32(0),detLabel = cms.string("TK")),
                                                          cms.PSet(detSelection = cms.uint32(3),detLabel = cms.string("TIB")),
                                                          cms.PSet(detSelection = cms.uint32(4),detLabel = cms.string("TID")),
                                                          cms.PSet(detSelection = cms.uint32(5),detLabel = cms.string("TOB")),
                                                          cms.PSet(detSelection = cms.uint32(6),detLabel = cms.string("TEC"))
                                                          )
                                )


process.p = cms.Path(process.pixClus*process.tkClus*process.default)

